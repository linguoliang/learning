#include "climb_stairs.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int Climb(vector<int>& cache, size_t i);

void ClimbStaris() {
  size_t n = 10;
  vector<int> cache(n + 1, -1);
  cout << Climb(cache, n) << endl;
}

int Climb(vector<int>& cache, size_t i) {
  if (cache[i] != -1) {
    return cache[i];
  }

  int ret;
  if (i == 0 || i == 1) {
    ret = 1;
  } else {
    ret = Climb(cache, i - 1) + Climb(cache, i - 2);
  }
  cache[i] = ret;
  return ret;
}
