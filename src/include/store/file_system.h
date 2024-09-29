#ifndef _STORE_FILE_SYSTEM_H_
#define _STORE_FILE_SYSTEM_H_

#include <string>

#include "status.h"

class FileSystem {
 public:
  FileSystem() = default;

  FileSystem(const FileSystem&) = delete;
  FileSystem& operator=(const FileSystem&) = delete;

  virtual ~FileSystem() = default;

  virtual leveldb::Status ReadFile(const std::string& file_name,
                                   std::string* data,
                                   size_t* len) = 0;

  // only overwrite not append write
  virtual leveldb::Status WriteFile(const std::string& file_name,
                                    const std::string& data) = 0;

  virtual leveldb::Status DeleteFile(const std::string& file_name) = 0;

  virtual bool FileExist(const std::string& file_name) = 0;
  virtual leveldb::Status CreateDir(const std::string& file_path) = 0;
};

#endif  // _STORE_FILE_SYSTEM_H_