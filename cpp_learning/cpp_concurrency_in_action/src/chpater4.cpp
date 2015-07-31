//
// Created by chaomai on 5/26/15.
//

#include "chpater4.h"

void chpater4ex1() {
  std::mutex m;
//  m.lock();
//  m.lock();

  std::unique_lock<std::mutex> ul(m);
  ul.lock();
  ul.lock();
}

void chpater4ex2() {
  threadsafe_queue<int> data_queue;

  auto data_preparation_thread = [&]() {
    for (int i = 0; i < 10; ++i) {
      int const data = i;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      data_queue.push(data);
    }
  };

  auto data_processing_thread = [&]() {
    while (true) {
      int data;
      data_queue.wait_and_pop(data);
      std::cout << data << std::endl;
    }
  };

  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();
}

void chpater4ex3() {
  std::future<int> the_answer = std::async([]() { return 1 + 1; });
  std::cout << "futuring..." << std::endl;
  std::cout << the_answer.get() << std::endl;
}

void chpater4ex4() {
  timer t;

  std::future<int> the_answer = std::async(std::launch::deferred, []() {
    for (int i = 0; i < 999999999; ++i) {
      int a = 0;
    }
    return 1 + 1;
  });
  std::cout << "futuring..." << std::endl;
  for (int i = 0; i < 999999999; ++i) {
    int a = 0;
  }
  std::cout << the_answer.get() << std::endl;
}

void chpater4ex5() {
  std::mutex m;
  std::deque<std::packaged_task<int(int)>> tasks;

  auto f1 = [&]() {
    while (true) {
      std::packaged_task<int(int)> task;
      {
        std::lock_guard<std::mutex> lk(m);
        if (tasks.empty()) {
          continue;
        }
        task = std::move(tasks.front());
        tasks.pop_front();
      }
      task(2);
    }
  };

  auto f2 = [&](int (*f)(int)) {
    std::packaged_task<int(int)> task(f);
    std::future<int> res = task.get_future();
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task));
    return res;
  };

  auto task = [](int b) {
    for (int i = 0; i < 99999999; ++i) {
      int a = 0;
    }
    return b;
  };

  std::thread t1(f1);
  std::thread t2(f2, task);

  t1.join();
  t2.join();
}

void chpater4ex6() {
  timer t;
  auto f = [](int b) {
    for (int i = 0; i < 999999999; ++i) {
      int a = 0;
    }
    return b;
  };

  std::packaged_task<int(int)> task(f);
  std::future<int> res = task.get_future();
  //waiting endlessly
  //res.wait();
  //std::cout << res.get() << std::endl;
  task(2);
  std::cout << res.get() << std::endl;
}

void chpater4ex7() {
  timer t;
  auto f = [](int b) {
    for (int i = 0; i < 999999999; ++i) {
      int a = 0;
    }
    return b;
  };

  std::packaged_task<int(int)> task(f);
  std::future<int> res = task.get_future();

  std::thread t1(std::move(task), 2);

  for (int i = 0; i < 999999999; ++i) {
    int a = 0;
  }

  t1.join();
}

void chpater4ex8() {
  std::packaged_task<int()> t;
  t();
}

void chpater4ex9() {
  auto f = [](int b) {
    for (long i = 0; i < 999999999; ++i) {
      int a = 0;
    }
    return b;
  };

  std::promise<int> p;
  p.set_value(f(2));
  auto fu = p.get_future();
  std::cout << fu.get() << std::endl;
}

void chpater4ex10() {
  auto a = std::chrono::system_clock::now();
  auto b = std::chrono::time_point_cast<std::chrono::hours>(a);

  std::cout << b.time_since_epoch().count();
}

void chpater4ex11() {
  std::list<int> a = {1, 2, 3, 4, 5};
  std::list<int> b = {10, 11, 12, 13, 14};

  std::list<int> res;
  std::cout << &(*a.begin()) << std::endl;
  res.splice(res.begin(), a);
  std::cout << &(*res.begin()) << std::endl;
  res.push_back(6);
  std::cout << &(*res.begin()) << std::endl;
  res.pop_front();
  std::cout << &(*res.begin()) << std::endl;
}

std::list<long> get_huge_list() {
  std::list<long> res;
  for (long i = 4100; i > 0; --i) {
    res.push_back(i);
  }

  return res;
}

void chpater4ex12() {
  timer t;
  auto res_list = sequential_quick_sort(get_huge_list());
//  print_list(res_list);
}

void chpater4ex13() {
  timer t;
  auto res_list = parallel_quick_sort(get_huge_list());
//  print_list(res_list);
}

void chpater4ex14(){
  std::vector<std::thread> ts;
  for (int i = 0; i < 10000; ++i) {
    ts.push_back(std::thread([](){
      int a = 0;
      a++;
      std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }));
  }

  std::for_each(ts.begin(), ts.end(), std::mem_fn(&std::thread::join));
}

void chpater4() {
  timer t;
  chpater4ex14();
}
