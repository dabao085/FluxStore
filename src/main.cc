#include <iostream>
#include "store/flux_store_client.h"

using namespace std;

int main(int argc, char* argv[]) {
  std::cout << "Hello FluxStore" << std::endl;
  FluxStoreCLI cli;
  cli.run(argc, argv);

  return 0;
}