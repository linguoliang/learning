#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::microseconds microseconds;

std::atomic<int> cnt = {0};

void f() {
  for (int n = 0; n < 1000000; ++n) {
    cnt.fetch_add(1, std::memory_order_relaxed);
    // cnt.fetch_add(1, std::memory_order_seq_cst);
  }
}

int main() {
  Clock::time_point t0 = Clock::now();

  std::vector<std::thread> v;
  for (int n = 0; n < 100; ++n) {
    v.emplace_back(f);
  }
  for (auto& t : v) {
    t.join();
  }
  std::cout << "Final counter value is " << cnt << '\n';

  Clock::time_point t1 = Clock::now();

  microseconds ms = std::chrono::duration_cast<microseconds>(t1 - t0);

  std::cout << ms.count() << std::endl;
}
