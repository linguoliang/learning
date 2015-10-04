//
// Created by chaomai on 5/18/15.
//

#include <thread>
#include "chpater3.h"

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(
    ULONG_MAX);

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) !=
         some_list.end();
}

class some_big_object {};

void swap(some_big_object &lhs, some_big_object &rhs);

class X {
 private:
  some_big_object some_detail;
  std::mutex m;

 public:
  X(some_big_object const &sd) : some_detail(sd) {}

  friend void swap(X &lhs, X &rhs) {
    if (&lhs == &rhs) return;
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    swap(lhs.some_detail, rhs.some_detail);
  }
};

void swap1(some_big_object &lhs, some_big_object &rhs);

class X1 {
 private:
  some_big_object some_detail;
  std::mutex m;

 public:
  X1(some_big_object const &sd) : some_detail(sd) {}

  friend void swap1(X1 &lhs, X1 &rhs) {
    if (&lhs == &rhs) return;
    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(lhs.m, std::defer_lock);
    std::lock(lock_a, lock_b);
    swap(lhs.some_detail, rhs.some_detail);
  }
};

void chpater3ex1() {
  std::mutex mutex1;
  mutex1.lock();
  std::cout << mutex1.try_lock() << std::endl;
}

void chpater3ex2() {
  std::mutex mutex1;
  std::cout << mutex1.try_lock() << std::endl;
}

void chapter3ex3() {
  std::mutex mutex;
  std::mutex mutex1;
  int res = 0;

  auto func1 = [&mutex, &mutex1, &res]() {
    std::cout << "run func1" << std::endl;
    res++;
  };

  auto func2 = [&mutex, &mutex1, &res]() {
    std::cout << "run func2" << std::endl;
    res++;
  };

  std::vector<std::thread> ts;

  for (int i = 0; i < 10000; ++i) {
    ts.push_back(std::thread(func1));
  }
  for (int i = 0; i < 10000; ++i) {
    ts.push_back(std::thread(func2));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));

  std::cout << res << std::endl;
}

void chapter3ex4() {
  std::mutex mutex;
  std::mutex mutex1;
  int res = 0;

  auto func1 = [&mutex, &mutex1, &res]() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    std::lock_guard<std::mutex> lock_guard1(mutex1);
    //    std::lock_guard<std::mutex> lock_guard1(mutex1);
    //    std::lock_guard<std::mutex> lock_guard(mutex);
    std::cout << "run func1" << std::endl;
    res++;
  };

  auto func2 = [&mutex, &mutex1, &res]() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    std::lock_guard<std::mutex> lock_guard1(mutex1);
    std::cout << "run func2" << std::endl;
    res++;
  };

  std::vector<std::thread> ts;

  for (int i = 0; i < 10000; ++i) {
    ts.push_back(std::thread(func1));
  }
  for (int i = 0; i < 10000; ++i) {
    ts.push_back(std::thread(func2));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));

  std::cout << res << std::endl;
}

void chapter3ex5() {
  std::mutex mutex;
  std::mutex mutex1;
  int res = 0;

  auto func1 = [&mutex, &mutex1, &res]() {
    std::lock(mutex, mutex1);

    std::lock_guard<std::mutex> lock_guard(mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lock_guard1(mutex1, std::adopt_lock);
    std::cout << "run func1" << std::endl;
    res++;
  };

  auto func2 = [&mutex, &mutex1, &res]() {
    std::lock(mutex, mutex1);

    // possible live lock here???
    //    std::lock(mutex1, mutex);

    std::lock_guard<std::mutex> lock_guard(mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lock_guard1(mutex1, std::adopt_lock);
    std::cout << "run func2" << std::endl;
    res++;
  };

  std::vector<std::thread> ts;

  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func1));
  }
  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func2));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));

  std::cout << res << std::endl;
}

void chapter3ex6() {
  std::mutex mutex;
  std::mutex mutex1;
  int res = 0;

  auto func1 = [&mutex, &mutex1, &res]() {
    std::unique_lock<std::mutex> unique_lock(mutex, std::defer_lock);
    std::unique_lock<std::mutex> unique_lock1(mutex1, std::defer_lock);
    std::lock(unique_lock, unique_lock1);

    std::cout << "run func1" << std::endl;
    res++;
  };

  auto func2 = [&mutex, &mutex1, &res]() {
    std::unique_lock<std::mutex> unique_lock(mutex, std::defer_lock);
    std::unique_lock<std::mutex> unique_lock1(mutex1, std::defer_lock);
    std::lock(unique_lock, unique_lock1);

    // possible live lock here???
    //    std::lock(unique_lock1, unique_lock);

    std::cout << "run func2" << std::endl;
    res++;
  };

  std::vector<std::thread> ts;

  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func1));
  }
  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func2));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));

  std::cout << res << std::endl;
}

void chapter3ex7() {
  std::mutex mutex;
  std::mutex mutex1;

  auto func1 = [&mutex, &mutex1]() {
    while (true) {
      std::lock_guard<std::mutex> lock_guard(mutex);
      std::lock_guard<std::mutex> lock_guard1(mutex1);
      //    std::lock_guard<std::mutex> lock_guard1(mutex1);
      //    std::lock_guard<std::mutex> lock_guard(mutex);
      std::cout << "run func1" << std::endl;
    }

  };

  auto func2 = [&mutex, &mutex1]() {
    while (true) {
      std::lock_guard<std::mutex> lock_guard(mutex);
      std::lock_guard<std::mutex> lock_guard1(mutex1);
      std::cout << "run func2" << std::endl;
    }
  };

  std::thread thread1(func1);
  std::thread thread2(func2);

  thread1.join();
  thread2.join();
}

void chapter3ex8() {
  std::mutex mutex;
  std::mutex mutex1;

  auto func1 = [&mutex, &mutex1]() {
    while (true) {
      std::lock(mutex, mutex1);

      std::lock_guard<std::mutex> lock_guard(mutex, std::adopt_lock);
      std::lock_guard<std::mutex> lock_guard1(mutex1, std::adopt_lock);
      std::cout << "run func1" << std::endl;
    }
  };

  auto func2 = [&mutex, &mutex1]() {
    while (true) {
      std::lock(mutex, mutex1);

      // possible live lock here???
      //    std::lock(mutex1, mutex);

      std::lock_guard<std::mutex> lock_guard(mutex, std::adopt_lock);
      std::lock_guard<std::mutex> lock_guard1(mutex1, std::adopt_lock);
      std::cout << "run func2" << std::endl;
    }
  };

  std::vector<std::thread> ts;

  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func1));
  }
  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func2));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));
}

void chapter3ex9() {
  std::mutex mutex;
  std::mutex mutex1;
  int res = 0;

  auto func1 = [&mutex, &mutex1, &res]() {
    std::unique_lock<std::mutex> unique_lock(mutex, std::defer_lock);
    std::unique_lock<std::mutex> unique_lock1(mutex1, std::defer_lock);
    std::lock(unique_lock, unique_lock1);

    std::cout << "run func1" << std::endl;
    res++;
  };

  auto func2 = [&mutex, &mutex1, &res]() {
    std::unique_lock<std::mutex> unique_lock(mutex, std::defer_lock);
    std::unique_lock<std::mutex> unique_lock1(mutex1, std::defer_lock);
    std::lock(unique_lock, unique_lock1);

    // possible live lock here???
    //    std::lock(unique_lock1, unique_lock);

    std::cout << "run func2" << std::endl;
    res++;
  };

  std::vector<std::thread> ts;

  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func1));
  }
  for (int i = 0; i < 5000; ++i) {
    ts.push_back(std::thread(func2));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));

  std::cout << res << std::endl;
}

void chpater3ex9() {
  std::thread t1;
  std::thread t2;
  auto f1 = [](std::thread t2) { t2.join(); };
  auto f2 = [](std::thread t1) { t1.join(); };

  //  t1 = std::thread(f1, t2);
  //  t2 = std::thread(f2, t1);
}

void chpater3ex10() {
  hierarchical_mutex high_level_mutex(10000);
  hierarchical_mutex low_level_mutex(5000);

  auto do_low_level_stuff = []() -> int {
    std::cout << "do low level stuff" << std::endl;
    return 1;
  };

  auto low_level_func = [&]() -> int {
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
  };

  auto high_level_stuff = [](int some_param) {
    std::cout << "high level stuff " << some_param << std::endl;
  };

  auto high_level_func = [&]() {
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
    high_level_stuff(low_level_func());
  };

  std::thread t(high_level_func);
  t.join();

  hierarchical_mutex other_mutex(100);

  auto do_other_stuff = []() { std::cout << "do other stuff" << std::endl; };

  auto other_stuff = [&]() {
    high_level_func();
    do_other_stuff();
  };

  std::thread t1([&]() {
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
  });
  t1.join();
}

void chpater3ex11() {
  std::mutex mutex1;
  std::mutex mutex2;

  //  {
  //    std::lock_guard<std::mutex> lock_guard(mutex1);
  //    auto lg = std::move(lock_guard);
  //  }

  {
    mutex1.lock();
    std::unique_lock<std::mutex> unique_lock(mutex1, std::adopt_lock);
    auto ul = std::move(unique_lock);
    ul.unlock();
    //    unique_lock.unlock();
    mutex2.lock();
  }
}

void chpater3() {
  //  chpater3ex1();
  //  chpater3ex2();
  //  chapter3ex3();
  //  chapter3ex4();

  // problems here
  //  chapter3ex5();
  //  chapter3ex6();
  //  chapter3ex7();
  //  chapter3ex8();

  //  chpater3ex9();
  //  chpater3ex10();
  chpater3ex11();
}
