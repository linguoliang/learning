// #ifndef _FIRST_H_
// #define _FIRST_H_

// #include "Second.h"
// #include <string>

// class Second;
// class First {
// friend void Second::fun();
// friend class Second;

// std::string str = "Dziala\n";

// public:
// First() = default;
// };
// #endif

#ifndef F_H_
#define F_H_

#include "Second.h"

class First {
  friend void Second::fun();

  std::string str = "Dziala\n";

 public:
  First() = default;
};

// void Second::fun() { std::cout << fObj.str; }
void Second::fun() { std::cout << fObj.size(); }

#endif /* ifndef F_H_ */
