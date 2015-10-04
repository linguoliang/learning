//
// Created by chaomai on 5/17/15.
//

#include "chpater2.h"

void do_work(double data) {
  for (long int i = 0; i < 999999999; ++i) {
    int a = 0;
  }
  data = 2.0;
  std::cout << data << std::endl;
}

void update_data(int id, double &data) { data = 2.0; }

class X {
 public:
  void do_work(int a) { std::cout << a << std::endl; };
};

void chpater2ex1() {
  int id = 1;
  double data = 1.0;

  //  std::thread t(update_data, id, std::ref(data));
  // won't work
  //  std::thread t(update_data, id, data);
  //  t.join();
  //  std::cout << data << std::endl;
  X x;
  std::thread t(&X::do_work, &x, id);
  t.join();
}

class thread_guard {
  std::thread &t;

 public:
  explicit thread_guard(std::thread &t_) : t(t_) {}

  ~thread_guard() {
    if (t.joinable()) {
      t.join();
    }
  }

  thread_guard(thread_guard const &p) = delete;

  thread_guard &operator=(thread_guard const &) = delete;
};

class scoped_thread {
  std::thread t;

 public:
  explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
    if (!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }

  ~scoped_thread() { t.join(); }

  scoped_thread(scoped_thread const &p) = delete;

  scoped_thread &operator=(scoped_thread const &) = delete;
};

void chpater2ex2() {
  //  std::thread t(do_work, 2);
  //  thread_guard guard(t);
  //  thread_guard guard(std::thread(do_work, 2));
  scoped_thread(std::thread(do_work, 2));
}

void chpater2ex3() {
  std::vector<int> to_add;
  for (int i = 0; i < 350000000; ++i) {
    to_add.push_back(i);
  }

  int res = 0;
  parallel_accumulate(to_add.begin(), to_add.end(), res);
  std::cout << res << std::endl;
}

void chpater2() { chpater2ex3(); }
