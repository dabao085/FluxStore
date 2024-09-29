#ifndef _STORE_FILE_INDEX_MEM_H_
#define _STORE_FILE_INDEX_MEM_H_

#include <mutex>
#include <unordered_map>
#include "file_index.h"

// file index is stored in memory
class FileIndexMem : public FileIndex {
 public:
  FileIndexMem() = default;
  FileIndexMem(const FileIndexMem&) = delete;
  FileIndexMem& operator=(const FileIndexMem&) = delete;

 public:
  void AddFile(const std::string& file_path,
               size_t file_size,
               const std::string& file_path_flux) override;
  bool RemoveFile(const std::string& file_path) override;
  bool GetFileMetadata(const std::string& file_path,
                       FileMetadata* metadata) override;
  bool FileExist(const std::string& file_path) override;
  void AccessFile(const std::string& file_path) override;

 public:
  std::unordered_map<std::string, FileMetadata> GetIndex();
  void SetIndex(const std::string& file_name, const FileMetadata& meta);

 private:
  // file_path -> metadata
  std::unordered_map<std::string, FileMetadata> index_;
  // protect mutex_
  std::mutex mutex_;
};
#endif  // _STORE_FILE_INDEX_MEM_H_