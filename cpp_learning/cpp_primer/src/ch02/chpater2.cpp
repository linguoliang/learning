#include <iostream>

int main() {
  std::cout << "/*";
  std::cout << "*/";
  // std::cout <</*"*/"*/;
  std::cout << /* "*/ " /* " /*" */ << std::endl;

  std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(long) << std::endl;
  std::cout << sizeof(long long) << std::endl;
  std::cout << sizeof(char) << std::endl;
  std::cout << sizeof(signed char) << std::endl;
  std::cout << sizeof(unsigned char) << std::endl;

  // unsigned char c = 257;
  // int intc = c;
  // std::cout << intc << std::endl;

  // signed char c2 = 256;
  // int intc2 = c2;
  // std::cout << intc2 << std::endl;

  long long ll = 1234567891234567891;
  std::cout << ll << std::endl;

  double d = ll;
  std::cout << d << std::endl;

  unsigned u = 10, u2 = 42;
  std::cout << u2 - u << std::endl;
  std::cout << u - u2 << std::endl;

  int i = 10, i2 = 42;
  std::cout << i2 - i << std::endl;
  std::cout << i - i2 << std::endl;
  std::cout << i - u << std::endl;
  std::cout << u - i << std::endl;

  std::cout << 4294967296 % 4294967296 << std::endl;

  std::cout << "2\tM\n" << std::endl;

  // std::cin >> int input;
}
