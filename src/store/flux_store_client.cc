#include "store/flux_store_client.h"
#include "glog/logging.h"

void FluxStoreCLI::upload(const std::string& file_path) {
  LOG(INFO) << "Uploading file: " << file_path;

  std::string data;
  leveldb::Status status;
  size_t file_size = 0;
  status = local_fs_->ReadFile(file_path, &data, &file_size);
  if (!status.ok()) {
    LOG(ERROR) << "Fail to read from local fs, file=" << file_path;
    return;
  }

  status = flux_fs_->WriteFile(file_path, data);
  if (!status.ok()) {
    LOG(ERROR) << "Fail to write to flux fs, file=" << file_path;
    return;
  }
}

void FluxStoreCLI::download(const std::string& file_path,
                            const std::string& destination) {
  LOG(INFO) << "Downloading file: " << file_path << " to " << destination;

  size_t file_size = flux_fs_->GetFileSize(file_path);
  if (file_size != 0) {
    std::string data;
    leveldb::Status status;
    status = flux_fs_->ReadFile(file_path, &data, &file_size);
    if (!status.ok()) {
      LOG(ERROR) << "Failed to read file " << file_path
                 << ", error=" << status.ToString();
      return;
    } else {
      status = local_fs_->WriteFile(destination, data);
      if (!status.ok()) {
        LOG(ERROR) << "Failed to write file " << destination
                   << ", error=" << status.ToString();
      }
    }
  } else {
    LOG(WARNING) << "size of file " << file_path << " is 0";
  }
}

void FluxStoreCLI::remove(const std::string& file_path) {
  LOG(INFO) << "Deleting file: " << file_path;
  // 调用具体的删除逻辑
  leveldb::Status status = flux_fs_->DeleteFile(file_path);
  if (!status.ok()) {
    LOG(ERROR) << "Failed to remove file " << file_path;
  }
}

void FluxStoreCLI::run(int argc, char* argv[]) {
  if (argc < 2) {
    LOG(ERROR) << "Usage: <command> <file_path> [destination]";
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
    LOG(ERROR) << "Invalid command or arguments.";
  }
}