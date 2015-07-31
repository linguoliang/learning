#include <iostream>

int main() {
  std::cout << "/*";
  std::cout << "*/";
  // std::cout <</*"*/"*/;
  std::cout << /* "*/ " /* " /*" */;

  std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(long) << std::endl;
  std::cout << sizeof(char) << std::endl;
  std::cout << sizeof(signed char) << std::endl;
  std::cout << sizeof(unsigned char) << std::endl;

  return 0;
}
