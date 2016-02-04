#ifndef UTIL_H_
#define UTIL_H_

#include <chrono>
#include <iostream>
#include <string>

std::string trimTail(const std::string &str, const std::string &toTrim);

class Timer {
 public:
  Timer() { starting_time = std::chrono::high_resolution_clock::now(); }

  ~Timer() {
    std::cout << "duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::high_resolution_clock::now() - starting_time)
                     .count()
              << std::endl;
  }

 private:
  std::chrono::high_resolution_clock::time_point starting_time;
};

#endif /* ifndef UTIL_H_ */
