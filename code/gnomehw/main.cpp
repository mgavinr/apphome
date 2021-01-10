#include <iostream>
//
//
#include "myGnomeApplication.h"

int main(int argc, char* argv[]) {
  auto rv = 0;
  std::cout << "Hello, World!" << std::endl;
  auto app = mygnome::myGnomeApplication(argc, argv);
  return rv;
}