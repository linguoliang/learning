//
// Created by chaomai on 5/26/15.
//

#ifndef CHPATER4_H
#define CHPATER4_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <iostream>
#include <thread>
#include <future>
#include <deque>
#include <list>
#include <algorithm>

#include "utils.h"

void chpater4();

template<typename T>
class threadsafe_queue {
 private:
  std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

 public:
  void push(T new_value) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
  }
};

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  T const &pivot = *result.begin();

  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](T const &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.begin(), input, input.begin(),
                    divide_point);
  auto new_lower(sequential_quick_sort(std::move(lower_part)));

  auto new_higher(sequential_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower);
  return result;
}

// problems!!!
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  T const &pivot = *result.begin();

  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](T const &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.begin(), input, input.begin(),
                    divide_point);

  std::future<std::list<T>> new_lower(
      std::async(std::launch::async, &parallel_quick_sort < T > ,
                 std::move(lower_part)));

  auto new_higher(parallel_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());

  return result;
}

template<typename T>
void print_list(std::list<T> input) {
  for (T t : input) {
    std::cout << t << " ";
  }
  std::cout << std::endl;
}

//template<typename F, typename A>
//std::future<std::result_of<F(A &&)>::type> spawn_task(F &&f, A &&a) {
//  typedef std::result_of<F(A &&)>::type result_type;
//  std::packaged_task<result_type(A &&)> task(std::move(f));
//  std::future<result_type> res(task.get_future());
//  std::thread t(std::move(task), std::move(a));
//  t.detach();
//  return res;
//}

// wtf???
template<typename T_>
using decay_t = typename std::decay<T_>::type;
template<class T>
using result_of_t = typename std::result_of<T>::type;

template<typename F, typename A>
std::future<result_of_t<decay_t<F>(decay_t<A>)>> spawn_task(F &&f, A &&a) {
  using result_t = result_of_t<decay_t<F>(decay_t<A>)>;
  std::packaged_task<result_t(decay_t<A>)> task(std::forward<F>(f));
  auto res = task.get_future();
  std::thread t(std::move(task), std::forward<A>(a));
  t.detach();
  return res;
}

#endif
