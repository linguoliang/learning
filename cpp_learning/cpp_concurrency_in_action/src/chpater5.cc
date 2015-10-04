//
// Created by chaomai on 6/1/15.
//

#include "chpater5.h"

void chpater5ex1(void);
void chpater5ex2(void);
void chpater5ex3(void);
void chpater5ex4(void);
void chpater5ex5(void);
void chpater5ex6(void);
void chpater5ex7(void);
void chpater5ex8(void);

void chpater5ex1() {
  struct data {
    int i;
    double d;
    unsigned bf1:10;
    int bf2:25;
    int :0;
    int bf4:9;
    char c1, c2;
    std::string s;
  };

  int b = 1000;

  data a;
  a.i = 1;
  a.d = 2.5;
}

void chpater5ex2() {
  struct data {
    int i;
    double d;
    unsigned bf1:10;
    int bf2:25;
    int :0;
    int bf4:9;
    char c1, c2;
    std::string s;
  };

  int b;
  std::atomic<int> a(1);
  std::atomic<long> c(100);
  std::atomic<int *> p(&b);
  a++;
  p--;
  c++;
  std::cout << a << std::endl;
  std::cout << p << std::endl;
  std::cout << c << std::endl;

  std::atomic_flag f = ATOMIC_FLAG_INIT;
}

void chpater5ex3() {
  timer t;
  int a = 0;
  spinlock_mutex sm;
  auto f1 = [&]() {
    for (int i = 0; i < 500000; ++i) {
      std::lock_guard<spinlock_mutex> lg(sm);
      a++;
    }
  };
  auto f2 = [&]() {
    for (int i = 0; i < 500000; ++i) {
      std::lock_guard<spinlock_mutex> lg(sm);
      a--;
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  t1.join();
  t2.join();

  std::cout << a << std::endl;
}

void chpater5ex4() {
  timer t;
  int a = 0;
  std::mutex sm;
  auto f1 = [&]() {
    for (int i = 0; i < 500000; ++i) {
      std::lock_guard<std::mutex> lg(sm);
      a++;
    }
  };
  auto f2 = [&]() {
    for (int i = 0; i < 500000; ++i) {
      std::lock_guard<std::mutex> lg(sm);
      a--;
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  t1.join();
  t2.join();

  std::cout << a << std::endl;
}

void chpater5ex5() {
  bool expected = false;
  std::atomic<bool> b;
  while (!b.compare_exchange_weak(expected, true) && !expected);
//  b.compare_exchange_strong(expected, true);
}

void chpater5ex6() {
  std::atomic<bool> b;
  std::cout << b.is_lock_free() << std::endl;

  /*
   * struct s {
   *   int a;
   *   int a1;
   * };
   * std::atomic<s> c;
   * std::cout << c.is_lock_free() << std::endl;
   */
}

void chpater5ex7() {
  class Foo { };
  Foo some_array[5];
  std::atomic<Foo *> p(some_array);
  Foo *x = p.fetch_add(2);
  assert(x == some_array);
  assert(p.load() == &some_array[2]);
  x = (p -= 1);
  assert(x == &some_array[1]);
  assert(p.load() == &some_array[1]);
}

void chpater5ex8(){
  std::atomic<bool> x, y;
  std::atomic<int> z;

  x = false;
  y = false;
  z = 0;
  std::thread a([&](){
      x.store(true, std::memory_order_seq_cst);
      });

  std::thread b([&](){
      y.store(true, std::memory_order_seq_cst);
      });

  std::thread c([&](){
      while (!x.load(std::memory_order_seq_cst));
      if (y.load(std::memory_order_seq_cst)) {
        ++z;
      }
      });
  std::thread d([&](){
      while (!y.load(std::memory_order_seq_cst));
      if (x.load(std::memory_order_seq_cst)) {
        ++z;
      }
      });

  a.join();
  b.join();
  c.join();
  d.join();
  std::cout << z << std::endl;
  assert(z.load() != 0);
  assert(z.load() == 0);
}

void chpater5() {
  chpater5ex8();
}
