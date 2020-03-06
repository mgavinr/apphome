#include <iostream>
#include <sstream>
#include <chrono>
#include "myformat.h"

int main(void) {
  std::cout << fmt::format("Hello name {} surname {} the {}", "Gavin", "Rogers", 3);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname", "Gavin", "Rogers", 3);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname");
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname {}");
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname {}", 1);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname {}", 1, 2);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello");
  std::cout << "\nEND\n";
  std::cout << fmt::format(1);
  std::cout << "\nEND\n";
  return 0;
}
