#ifndef _STORE_FILE_INDEX_H_
#define _STORE_FILE_INDEX_H_

#include <ctime>
#include <string>

struct FileMetadata {
  std::string file_path;
  std::string file_path_flux;  // path in FluxStore
  size_t file_size;
  std::time_t creation_time;
  std::time_t modification_time;
};

class FileIndex {
 public:
  FileIndex() = default;

  FileIndex(const FileIndex&) = delete;
  FileIndex& operator=(const FileIndex&) = delete;

  virtual ~FileIndex() = default;

  virtual void AddFile(const std::string& file_path,
                       size_t file_size,
                       const std::string& file_path_flux) = 0;
  virtual bool RemoveFile(const std::string& file_path) = 0;
  virtual bool GetFileMetadata(const std::string& file_path,
                               FileMetadata* metadata) = 0;
  virtual bool FileExist(const std::string& file_path) = 0;
  // update modification_time
  virtual void AccessFile(const std::string& file_path) = 0;
};

#endif  // _STORE_FILE_INDEX_H_