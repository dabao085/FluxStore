#ifndef _STORE_FLUX_FILE_SYSTEM_H_
#define _STORE_FLUX_FILE_SYSTEM_H_

#include <iostream>
#include <memory>
#include "file_system.h"
#include "local_file_system.h"

const std::string kFluxStoreDataPath = "/flux_store_data";
const std::string kFluxStoreJsonPath = "file_index.json";

class FileIndex;

class FluxFileSystem : public FileSystem {
 public:
  FluxFileSystem()
      : file_index_(std::make_shared<FileIndexJson>()),
        fs_(std::make_shared<LocalFileSystem>(file_index_)),
        mount_path_(kFluxStoreDataPath) {
    if (mount_path_.back() != '/') {
      mount_path_.push_back('/');
    }

    // XXX: check if mount_path_ exists, create it if necessary.
    if (!fs_->FileExist(mount_path_)) {
      leveldb::Status status = fs_->CreateDir(mount_path_);
      if (!status.ok()) {
        std::cerr << "Fail to create dir " << mount_path_ << std::endl;
      }
    }

    file_index_->LoadIndexFromFile(kFluxStoreJsonPath);
  }

  ~FluxFileSystem() { file_index_->SaveIndexToFile(kFluxStoreJsonPath); }

  leveldb::Status ReadFile(const std::string& file_name,
                           std::string* data,
                           size_t* len) override;

  leveldb::Status WriteFile(const std::string& file_name,
                            const std::string& data) override;

  leveldb::Status DeleteFile(const std::string& file_name) override;

  bool FileExist(const std::string& file_name) override;

  leveldb::Status CreateDir(const std::string& file_path) override;

  size_t GetFileSize(const std::string& file_name) const;

 private:
  std::shared_ptr<FileIndexJson> file_index_;
  std::shared_ptr<LocalFileSystem> fs_;
  std::string mount_path_;  // /flux_store_data for example
};

#endif  // _STORE_FLUX_FILE_SYSTEM_H_