// #ifndef _SECOND_H_
// #define _SECOND_H_

// #include <iostream>
// #include "First.h"

// class Second {
// First fObj;

// public:
// Second() = default;
// void fun() { std::cout << fObj.str; }
// };
// #endif

#ifndef S_H_
#define S_H_

// #include "First.h"

#include <iostream>

class First;

class Second {
  First& fObj;

 public:
  Second(First& rfObj) : fObj(rfObj) {}
  void fun();
};

class First {
  friend void Second::fun();

  std::string str = "Dziala\n";

 public:
  First() = default;
};

void Second::fun() { std::cout << fObj.str; }

#endif /* ifndef S_H_ */
