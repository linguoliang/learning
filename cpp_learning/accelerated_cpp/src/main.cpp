#include <iostream>

int main()
{
  std::cout << "Name?";
  std::string name;
  std::cin >> name;
  std::cout << "hello, " << name << std::endl << "yours?";
  std::cin >> name;
  std::cout << "hello, " << name << std::endl;
  return 0;
}
