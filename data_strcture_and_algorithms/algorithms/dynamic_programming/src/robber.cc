#include "robber.h"

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::vector;

int MaxRobbed(vector<int>& nums, vector<int>& cache, size_t i);

void Robber() {
  vector<int> nums{1, 2, 3, 4, 5, 10};

  // if numbers are {2, 1}, then the MaxRobbed() will direct return without
  // checking the first number. insert two 0 for these cases.
  nums.insert(nums.begin(), 2, 0);

  vector<int> cache(nums.size(), -1);
  cout << MaxRobbed(nums, cache, nums.size() - 1) << endl;
}

int MaxRobbed(vector<int>& nums, vector<int>& cache, size_t i) {
  if (cache[i] != -1) {
    return cache[i];
  }

  int ret;
  if (i == 0 || i == 1) {
    ret = nums[i];
  } else {
    ret = max(MaxRobbed(nums, cache, i - 1),
              MaxRobbed(nums, cache, i - 2) + nums[i]);
  }

  cache[i] = ret;
  return ret;
}
