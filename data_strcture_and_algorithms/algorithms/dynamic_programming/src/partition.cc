#include "partition.h"

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::min;
using std::sort;
using std::vector;

#include "util.h"

bool Partition1(const vector<int>& nums);
bool Part1(const vector<int>& nums, int i, int remains);
bool Partition2(const vector<int>& nums);
bool Partition3(const vector<int>& nums);
bool Partition4(const vector<int>& nums);

void Partition() {
  vector<int> nums{3, 1, 5, 9, 12};
  // vector<int> nums{10};
  // vector<int> nums{10, 2, 1, 1};
  // vector<int> nums{10, 2, 1, 1, 8, 9, 10, 11, 1};
  // vector<int> nums{1, 1, 2, 10};
  cout << Partition1(nums) << endl;
  cout << Partition2(nums) << endl;
  cout << Partition3(nums) << endl;
  cout << Partition4(nums) << endl;
}

bool Partition1(const vector<int>& nums) {
  int sum = 0;
  for (int num : nums) {
    sum += num;
  }

  if (sum % 2) {
    return false;
  }

  return Part1(nums, nums.size() - 1, sum / 2);
}

bool Part1(const vector<int>& nums, int i, int remains) {
  if (remains < 0) {
    return false;
  }

  if (remains == 0) {
    return true;
  }

  if (i == 0 && remains > 0) {
    return false;
  }

  return Part1(nums, i - 1, remains - nums[i]) || Part1(nums, i - 1, remains);
}

bool Partition2(const vector<int>& nums) {
  int sum = 0;
  for (int num : nums) {
    sum += num;
  }

  if (sum % 2) {
    return false;
  }

  int n = nums.size();
  int remains = sum / 2;

  // the dp[i][j] means whether possible to find a subset in nums[0, ..., j]
  // that are summed to remains.
  vector<vector<bool>> dp(n + 1, vector<bool>(remains + 1, false));

  for (int i = 0; i <= n; ++i) {
    dp[i][0] = true;
  }

  for (int i = 1; i <= remains; ++i) {
    dp[0][i] = false;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= remains; ++j) {
      // 不选j来构造subset，因此等于d[i-1][j]。
      dp[i][j] = dp[i - 1][j];

      if (j >= nums[i]) {
        dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
      }
    }
  }

  return dp[n][remains];
}

bool Partition3(const vector<int>& nums) {
  int sum = 0;
  for (int num : nums) {
    sum += num;
  }

  if (sum % 2) {
    return false;
  }

  int n = nums.size();
  // dp[i]代表可以从nums中构造一个subset，使得这个subset的和是i。
  vector<bool> dp(sum + 1, false);
  dp[0] = true;

  for (int i = 0; i < n; ++i) {
    // 之所以从sum倒着开始，是为了避免重复。
    // 每次dp[j]为true，是把j后面的某个element设为true。
    for (int j = sum; j >= 0; --j) {
      if (dp[j]) {
        dp[j + nums[i]] = true;
      }
    }
  }

  return dp[sum / 2];
}

bool Partition4(const vector<int>& nums) {
  int sum = 0;
  for (int num : nums) {
    sum += num;
  }

  if (sum % 2) {
    return false;
  }

  int n = nums.size();
  vector<bool> dp(sum + 1, false);
  dp[0] = true;
  int r = 0;

  vector<int> c(nums);
  // 让大的number在后面，使得下面的r尽可能慢的向右边移动。
  sort(c.begin(), c.end());

  for (int i = 0; i < n; ++i) {
    for (int j = r; j >= 0; --j) {
      if (dp[j]) {
        dp[j + c[i]] = true;
      }
    }

    // 其实最后只关心sum/2位置的情况，没有必要管后一半的情况。
    // 每次j只需要从最右边true的地方开始即可。
    r = min(sum / 2, r + c[i]);
  }

  return dp[sum / 2];
}
