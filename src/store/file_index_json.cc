#include "store/file_index_json.h"
#include <iostream>
#include "json.hpp"

void FileIndexJson::AddFile(const std::string& file_path,
                            size_t file_size,
                            const std::string& file_path_flux) {
  if (index_adapter_ != nullptr) {
    index_adapter_->AddFile(file_path, file_size, file_path_flux);
  }
}

bool FileIndexJson::RemoveFile(const std::string& file_path) {
  if (index_adapter_ != nullptr) {
    return index_adapter_->RemoveFile(file_path);
  }

  return false;
}

bool FileIndexJson::GetFileMetadata(const std::string& file_path,
                                    FileMetadata* metadata) {
  if (index_adapter_ != nullptr) {
    return index_adapter_->GetFileMetadata(file_path, metadata);
  }

  return false;
}

bool FileIndexJson::FileExist(const std::string& file_path) {
  if (index_adapter_ != nullptr) {
    return index_adapter_->FileExist(file_path);
  }

  return false;
}

void FileIndexJson::AccessFile(const std::string& file_path) {
  if (index_adapter_ != nullptr) {
    index_adapter_->AccessFile(file_path);
  }
}

void FileIndexJson::SaveIndexToFile(const std::string& filename) {
  if (index_adapter_ != nullptr) {
    nlohmann::json json_index;
    auto index = index_adapter_->GetIndex();
    for (const auto& entry : index) {
      json_index[entry.first] = {
          {"file_path", entry.second.file_path},
          {"file_path_flux", entry.second.file_path_flux},
          {"file_size", entry.second.file_size},
          {"creation_time", entry.second.creation_time},
          {"modification_time", entry.second.modification_time}};
    }

    std::ofstream ofs(filename);
    ofs << json_index.dump(4);  // 格式化保存为JSON文件
  }
}

void FileIndexJson::LoadIndexFromFile(const std::string& filename) {
  if (index_adapter_ != nullptr) {
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
      nlohmann::json json_index;
      ifs >> json_index;

      // C++17
      //      for (auto& [file_path, metadata_json] : json_index.items()) {
      //        FileMetadata metadata = {
      //            metadata_json["file_path"], metadata_json["file_size"],
      //            metadata_json["creation_time"],
      //            metadata_json["modification_time"]};
      //        index_adapter_->SetIndex(file_path, metadata);
      //      }

      for (auto& item : json_index.items()) {
        const std::string& file_path = item.key();
        const nlohmann::json& metadata_json = item.value();

        FileMetadata metadata = {
            metadata_json["file_path"], metadata_json["file_path_flux"],
            metadata_json["file_size"], metadata_json["creation_time"],
            metadata_json["modification_time"]};
        index_adapter_->SetIndex(file_path, metadata);
      }
    } else {
      std::cerr << "Missing json file=" << filename << std::endl;
    }
  }
}
