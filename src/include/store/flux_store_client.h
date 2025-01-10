#ifndef _STORE_FLUX_STORE_CLIENT_H_
#define _STORE_FLUX_STORE_CLIENT_H_

#include <iostream>
#include <memory>
#include "flux_file_system.h"
#include "local_file_system.h"

class FluxStoreCLI {
 public:
  FluxStoreCLI()
      : local_fs_(std::make_shared<LocalFileSystem>()),
        flux_fs_(std::make_shared<FluxFileSystem>()) {}

 public:
  bool Run(int argc, char* argv[]);

 private:
  bool Upload(const std::string& file_path);

  bool Download(const std::string& file_path, const std::string& destination);

  bool Remove(const std::string& file_path);

 private:
  std::shared_ptr<LocalFileSystem> local_fs_;
  std::shared_ptr<FluxFileSystem> flux_fs_;
};

#endif  // _STORE_FLUX_STORE_CLIENT_H_