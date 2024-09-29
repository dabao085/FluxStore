#ifndef _STORE_FILE_INDEX_JSON_H_
#define _STORE_FILE_INDEX_JSON_H_

#include <fstream>
#include <memory>
#include "file_index_mem.h"

// file index is persistent and stored in Json file.
class FileIndexJson : public FileIndex {
 public:
  FileIndexJson() : index_adapter_(std::make_unique<FileIndexMem>()) {}
  FileIndexJson(const FileIndexJson&) = delete;
  FileIndexJson& operator=(const FileIndexJson&) = delete;

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
  void SaveIndexToFile(const std::string& filename);
  void LoadIndexFromFile(const std::string& filename);

 private:
  std::unique_ptr<FileIndexMem> index_adapter_;
};

#endif  // _STORE_FILE_INDEX_JSON_H_