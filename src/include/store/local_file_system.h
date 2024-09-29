#ifndef _STORE_LOCAL_FILE_SYSTEM_H_
#define _STORE_LOCAL_FILE_SYSTEM_H_

#include <memory>
#include "file_system.h"
#include "store/file_index_json.h"

class LocalFileSystem : public FileSystem {
 public:
  // use FileIndexMem in default
  LocalFileSystem() : file_index_(std::make_shared<FileIndexMem>()) {}
  LocalFileSystem(const std::shared_ptr<FileIndex>& file_index)
      : file_index_(file_index) {}

  ~LocalFileSystem() = default;

  leveldb::Status ReadFile(const std::string& file_name,
                           std::string* data,
                           size_t* len) override;

  leveldb::Status WriteFile(const std::string& file_name,
                            const std::string& data) override;

  leveldb::Status DeleteFile(const std::string& file_name) override;

  bool FileExist(const std::string& file_name) override;

  leveldb::Status CreateDir(const std::string& file_path) override;

 private:
  std::shared_ptr<FileIndex> file_index_;
};

#endif  // _STORE_LOCAL_FILE_SYSTEM_H_