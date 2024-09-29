#include "store/file_index_mem.h"

void FileIndexMem::AddFile(const std::string& file_path,
                           size_t file_size,
                           const std::string& file_path_flux) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::time_t now = std::time(nullptr);
  FileMetadata metadata = {file_path, file_path_flux, file_size, now, now};
  index_[file_path] = metadata;
}

bool FileIndexMem::RemoveFile(const std::string& file_path) {
  std::lock_guard<std::mutex> lock(mutex_);
  return index_.erase(file_path) > 0;
}

bool FileIndexMem::GetFileMetadata(const std::string& file_path,
                                   FileMetadata* metadata) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = index_.find(file_path);
  if (it != index_.end()) {
    *metadata = it->second;
    return true;
  }
  return false;
}

bool FileIndexMem::FileExist(const std::string& file_path) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = index_.find(file_path);
  if (it != index_.end()) {
    return true;
  }
  return false;
}

void FileIndexMem::AccessFile(const std::string& file_path) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = index_.find(file_path);
  if (it != index_.end()) {
    it->second.modification_time = std::time(nullptr);
  }
}

std::unordered_map<std::string, FileMetadata> FileIndexMem::GetIndex() {
  std::lock_guard<std::mutex> lock(mutex_);
  return index_;
}

void FileIndexMem::SetIndex(const std::string& file_name,
                            const FileMetadata& meta) {
  std::lock_guard<std::mutex> lock(mutex_);
  index_[file_name] = meta;
}