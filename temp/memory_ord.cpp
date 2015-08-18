#include <iostream>
#include <atomic>
#include <thread>

void test() {
  int x;
  int x_init = true;
  int y = 100;

  auto f1 = [&]() {
    x = 42;
    x_init = true;
  };
  auto f2 = [&]() {
    while (!x_init) {
      y = x;
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  t1.join();
  t2.join();

  std::cout << y << std::endl;
}

void test1() {
  int x;
  std::atomic<bool> x_init;
  int y = 100;

  auto f1 = [&]() {
    x = 42;
    x_init.store(true);
  };
  auto f2 = [&]() {
    while (!x_init.load()) {
      y = x;
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  t1.join();
  t2.join();

  std::cout << y << std::endl;
}

void test2() {
  std::atomic_int x;
  std::atomic<bool> x_init;
  std::atomic_int y;
  y.store(100);

  auto f1 = [&]() {
    x.store(42);
    x_init.store(true);
  };
  auto f2 = [&]() {
    while (!x_init.load()) {
      y.store(x.load());
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  t1.join();
  t2.join();

  std::cout << y << std::endl;
}

int main(void) {
  test1();
  return 0;
}
