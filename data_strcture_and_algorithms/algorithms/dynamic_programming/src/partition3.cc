#include "partition3.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

bool Part1(const vector<int>& nums);
bool P1(const vector<int>& nums, int remains1, int remains2, int i);
bool Part2(const vector<int>& nums);

void Partition3() {
  // vector<int> nums{1, 2, 3, 3, 4, 5};
  vector<int> nums{1, 2, 3, 3, 4, 5, 900};
  cout << Part1(nums) << endl;
  cout << Part2(nums) << endl;
}

bool Part1(const vector<int>& nums) {
  int sum = 0;

  for (int num : nums) {
    sum += num;
  }

  if (sum % 3) {
    return false;
  }

  int remains = sum / 3;

  return P1(nums, remains, remains, nums.size() - 1);
}

bool P1(const vector<int>& nums, int remains1, int remains2, int i) {
  if (remains1 < 0 || remains2 < 0) {
    return false;
  }

  if (remains1 == 0 && remains2 == 0) {
    return true;
  }

  if (i == 0 && (remains1 > 0 || remains2 > 0)) {
    return false;
  }

  return P1(nums, remains1, remains2, i - 1) ||
         P1(nums, remains1 - nums[i], remains2, i - 1) ||
         P1(nums, remains1, remains2 - nums[i], i - 1);
}

bool Part2(const vector<int>& nums) {
  int sum = 0;

  for (int num : nums) {
    sum += num;
  }

  if (sum % 3) {
    return false;
  }

  int n = nums.size();
  vector<vector<bool>> dp(sum + 1, vector<bool>(sum + 1, false));
  dp[0][0] = true;

  // 优化方法类似2 partition problem。
  for (int i = 0; i < n; ++i) {
    for (int j = sum; j >= 0; --j) {
      for (int k = sum; k >= 0; --k) {
        if (dp[j][k]) {
          dp[j + nums[i]][k] = true;
          dp[j][k + nums[i]] = true;
        }
      }
    }
  }

  return dp[sum / 3][sum / 3];
}
