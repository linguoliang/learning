#include <thread>
#include <vector>

using std::thread;
using std::vector;

int main() {
  vector<thread> ts;

  for (int i = 0; i != 4; ++i) {
    ts.push_back(thread([]() {
      int a = 0;
      for (unsigned long i = 0; i < 10000000000000; ++i) {
        a += 2;
      }
    }));
  }

  for (auto &t : ts) {
    t.join();
  }
  return 0;
}
