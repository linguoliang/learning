//
// Created by chaomai on 5/14/15.
//

#include "chpater1.h"

void hello() { std::cout << "Hello Concurrent World" << std::endl; }

struct func {
  void operator()() {
    std::cout << "func" << std::endl;
    for (long int i = 0; i < 9999999999; ++i) {
      int a{0};
    }
  }
};

void chpater1() {
  func my_func;
  std::thread t(my_func);
  //  for (long int i = 0; i < 9999999; ++i) {
  //    int a{0};
  //  }
  std::cout << t.joinable() << std::endl;
  t.join();
  //  t.detach();
  std::cout << "chpater 1" << std::endl;
}
