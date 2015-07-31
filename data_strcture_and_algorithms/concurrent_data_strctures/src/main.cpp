#include <iostream>
#include <thread>

#include "harris_linked_list.h"

int main(int argc, char *argv[]) {
  List<int> list;

  std::thread a([&]() {
    for (int i = 0; i < 100; ++i) {
      list.insert_key(i);
    }
  });
  // std::thread b([&]() {
  //   for (int i = 100; i < 200; ++i) {
  //     list.insert_key(i);
  //   }
  // });
  // std::thread c([&]() {
  //   for (int i = 200; i < 300; ++i) {
  //     list.insert_key(i);
  //   }
  // });
  //
  // a.join();
  // b.join();
  // c.join();
  //
  return 0;
}
