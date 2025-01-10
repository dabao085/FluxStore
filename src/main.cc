#include <iostream>
#include "glog/logging.h"
#include "store/flux_store_client.h"

DEFINE_string(flux_store_data_path,
              "/flux_store_data",
              "flux backend data storage path");
DEFINE_string(flux_store_json_path,
              "file_index.json",
              "flux file index json file storage path");

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  LOG(ERROR) << "Hello FluxStore";
  FluxStoreCLI cli;
  bool ret = cli.Run(argc, argv);
  if (!ret) {
    LOG(ERROR) << "Fail to run FluxStoreClI::Run";
  }

  google::ShutdownGoogleLogging();
  return 0;
}