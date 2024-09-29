#include "store/flux_file_system.h"
#include <unistd.h>

leveldb::Status FluxFileSystem::ReadFile(const std::string& file_name,
                                         std::string* data,
                                         size_t* len) {
  if (fs_ != nullptr) {
    std::string file_name_in_flux;
    if (file_name.front() == '/') {
      file_name_in_flux = mount_path_ + file_name.substr(1);
    } else {
      file_name_in_flux = mount_path_ + file_name;
    }

    leveldb::Status status = fs_->ReadFile(file_name_in_flux, data, len);
    if (status.ok()) {
      file_index_->AccessFile(file_name);
    }

    return status;
  }

  return leveldb::Status::NotFound("Fail to read file " + file_name);
}

leveldb::Status FluxFileSystem::WriteFile(const std::string& file_name,
                                          const std::string& data) {
  if (fs_ != nullptr) {
    std::string file_name_in_flux;
    if (file_name.front() == '/') {
      file_name_in_flux = mount_path_ + file_name.substr(1);
    } else {
      file_name_in_flux = mount_path_ + file_name;
    }

    leveldb::Status status = fs_->WriteFile(file_name_in_flux, data);
    if (status.ok()) {
      file_index_->AddFile(file_name, data.size(), file_name_in_flux);
    }

    return status;
  }

  return leveldb::Status::NotFound("Fail to write file " + file_name);
}

leveldb::Status FluxFileSystem::DeleteFile(const std::string& file_name) {
  if (fs_ != nullptr) {
    std::string file_name_in_flux;
    if (file_name.front() == '/') {
      file_name_in_flux = mount_path_ + file_name.substr(1);
    } else {
      file_name_in_flux = mount_path_ + file_name;
    }

    leveldb::Status status = fs_->DeleteFile(file_name_in_flux);
    if (status.ok()) {
      file_index_->RemoveFile(file_name);
    }

    return status;
  }

  return leveldb::Status::NotFound("Fail to delete file " + file_name);
}

bool FluxFileSystem::FileExist(const std::string& file_name) {
  std::string file_name_in_flux;
  if (file_name.front() == '/') {
    file_name_in_flux = mount_path_ + file_name.substr(1);
  } else {
    file_name_in_flux = mount_path_ + file_name;
  }

  if (file_index_->FileExist(file_name)) {
    return true;
  }

  return ::access(file_name_in_flux.c_str(), F_OK) == 0;
}

leveldb::Status FluxFileSystem::CreateDir(const std::string& file_path) {
  if (fs_ != nullptr) {
    return fs_->CreateDir(file_path);
  }

  return leveldb::Status::IOError("Fail to create dir " + file_path);
}

size_t FluxFileSystem::GetFileSize(const std::string& file_name) const {
  FileMetadata metadata;
  if (file_index_->GetFileMetadata(file_name, &metadata)) {
    return metadata.file_size;
  }

  std::cerr << "Fail to get file size, file=" << file_name << std::endl;
  return 0;
}