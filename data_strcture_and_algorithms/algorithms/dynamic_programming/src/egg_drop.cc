#include "egg_drop.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#include "util.h"

using std::cout;
using std::endl;
using std::min;
using std::max;
using std::vector;

int Drop1(vector<vector<int>> &cache, int n, int k);
int Drop2(int n, int k);

void EggDrop() {
  int n = 4;
  int k = 36;

  vector<vector<int>> cache(n + 1, vector<int>(k + 1, -1));
  cout << Drop1(cache, n, k) << endl;
  cout << Drop2(n, k) << endl;
}

// the k is not actually floor you are at, it's the amount of floors to
// remaining test.
int Drop1(vector<vector<int>> &cache, int n, int k) {
  if (k == 1 || k == 0) {
    return k;
  }

  if (n == 1) {
    return k;
  }

  if (cache[n][k] != -1) {
    return cache[n][k];
  }

  int cur_min = INT_MAX;
  for (int i = 1; i <= k; ++i) {
    int cur_max = max(Drop1(cache, n - 1, i - 1), Drop1(cache, n, k - i));
    cur_min = min(cur_min, cur_max);
  }

  cache[n][k] = cur_min + 1;
  return cache[n][k];
}

int Drop2(int n, int k) {
  vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));

  for (int i = 0; i <= n; ++i) {
    dp[i][1] = 1;
    dp[i][0] = 0;
  }

  for (int j = 0; j <= k; ++j) {
    dp[1][j] = j;
  }

  // the case of 0, 1 in k and 1 in n is already set
  // so the i and j should not start from 0 or 1.
  for (int i = 2; i <= k; ++i) {
    for (int j = 2; j <= n; ++j) {
      int cur_min = INT_MAX;

      for (int m = 1; m <= i; ++m) {
        int cur_max = max(dp[j - 1][m - 1], dp[j][i - m]);
        cur_min = min(cur_min, cur_max);
      }
      dp[j][i] = cur_min + 1;
    }
  }

  return dp[n][k];
}
