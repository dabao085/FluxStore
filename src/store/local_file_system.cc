#include "store/local_file_system.h"
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "store/status.h"

leveldb::Status LocalFileSystem::ReadFile(const std::string& file_name,
                                          std::string* data,
                                          size_t* len) {
  std::ifstream file(file_name, std::ios::binary);
  if (!file.is_open()) {
    return leveldb::Status::IOError("Unable to open file: " + file_name);
  }

  file.seekg(0, std::ios::end);
  data->resize(file.tellg());
  *len = file.tellg();
  file.seekg(0, std::ios::beg);
  file.read(&(*data)[0], data->size());
  file.close();
  return leveldb::Status::OK();
}

leveldb::Status LocalFileSystem::WriteFile(const std::string& file_name,
                                           const std::string& data) {
  std::ofstream file(file_name, std::ios::binary);
  if (!file.is_open()) {
    return leveldb::Status::IOError("Unable to open file for writing: " +
                                    file_name);
  }

  // overwrite from begin
  file.write(data.c_str(), data.size());
  file.close();
  return leveldb::Status::OK();
}

leveldb::Status LocalFileSystem::DeleteFile(const std::string& file_name) {
  if (std::remove(file_name.c_str()) != 0) {
    return leveldb::Status::IOError("Unable to delete file: " + file_name);
  }

  return leveldb::Status::OK();
}

bool LocalFileSystem::FileExist(const std::string& file_name) {
  return ::access(file_name.c_str(), F_OK) == 0;
}

leveldb::Status LocalFileSystem::CreateDir(const std::string& file_path) {
  if (::mkdir(file_path.c_str(), 0755) == 0) {
    return leveldb::Status::OK();  // 成功创建目录
  } else {
    // 错误处理，根据errno返回相应的错误信息
    if (errno == EEXIST) {
      std::cout << "Directory already exists: " + file_path << std::endl;
      return leveldb::Status::OK();
    } else {
      return leveldb::Status::IOError("Failed to create directory: " +
                                      file_path);
    }
  }
}