#ifndef UTIL_H_
#define UTIL_H_

#include <algorithm>
#include <chrono>
#include <iostream>
#include <tuple>

class timer {
 public:
  timer() { starting_time = std::chrono::high_resolution_clock::now(); }

  ~timer() {
    std::cout << "duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::high_resolution_clock::now() - starting_time)
                     .count()
              << std::endl;
  }

 private:
  std::chrono::high_resolution_clock::time_point starting_time;
};

template <typename T>
void PrintArray(std::vector<std::vector<T>> arr) {
  std::cout << std::endl;
  for (auto i : arr) {
    for (auto j : i) {
      std::cout << j << "\t";
    }
    std::cout << std::endl;
  }
}

template <typename T>
void PrintArray(std::vector<T> arr) {
  std::cout << std::endl;
  for (auto i : arr) {
    std::cout << i << "\t";
  }
  std::cout << std::endl;
}

template <typename T>
T max(T a, T b, T c) {
  return std::max(std::max(a, b), c);
}

template <typename T>
T min(T a, T b, T c) {
  return std::min(std::min(a, b), c);
}

#endif
