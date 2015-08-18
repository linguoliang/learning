#include <iostream>
#include <atomic>

int main(void) {
  std::atomic<bool> x;
  if (x.load()) {
    std::cout << "true" << std::endl;
  }
  std::cout << "false" << std::endl;
  return 0;
}
