#include "store/flux_store_client.h"

void FluxStoreCLI::upload(const std::string& file_path) {
  std::cout << "Uploading file: " << file_path << std::endl;

  std::string data;
  leveldb::Status status;
  size_t file_size = 0;
  status = local_fs_->ReadFile(file_path, &data, &file_size);
  if (!status.ok()) {
    std::cerr << "Fail to read from local fs, file=" << file_path << std::endl;
    return;
  }

  status = flux_fs_->WriteFile(file_path, data);
  if (!status.ok()) {
    std::cerr << "Fail to write to flux fs, file=" << file_path << std::endl;
    return;
  }
}

void FluxStoreCLI::download(const std::string& file_path,
                            const std::string& destination) {
  std::cout << "Downloading file: " << file_path << " to " << destination
            << std::endl;

  size_t file_size = flux_fs_->GetFileSize(file_path);
  if (file_size != 0) {
    std::string data;
    leveldb::Status status;
    status = flux_fs_->ReadFile(file_path, &data, &file_size);
    if (!status.ok()) {
      std::cerr << "Failed to read file " << file_path
                << ", error=" << status.ToString() << std::endl;
      return;
    } else {
      status = local_fs_->WriteFile(destination, data);
      if (!status.ok()) {
        std::cerr << "Failed to write file " << destination
                  << ", error=" << status.ToString() << std::endl;
      }
    }
  } else {
    std::cout << "size of file " << file_path << " is 0" << std::endl;
  }
}

void FluxStoreCLI::remove(const std::string& file_path) {
  std::cout << "Deleting file: " << file_path << std::endl;
  // 调用具体的删除逻辑
  leveldb::Status status = flux_fs_->DeleteFile(file_path);
  if (!status.ok()) {
    std::cerr << "Failed to remove file " << file_path << std::endl;
  }
}

void FluxStoreCLI::run(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: <command> <file_path> [destination]" << std::endl;
    return;
  }

  const std::string command(argv[1]);
  if (command == "upload" && argc == 3) {
    upload(argv[2]);
  } else if (command == "download" && argc == 4) {
    download(argv[2], argv[3]);
  } else if (command == "delete" && argc == 3) {
    remove(argv[2]);
  } else {
    std::cout << "Invalid command or arguments." << std::endl;
  }
}