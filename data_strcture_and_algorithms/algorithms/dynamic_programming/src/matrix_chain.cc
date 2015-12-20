#include "matrix_chain.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#include "util.h"

using std::min;
using std::cout;
using std::endl;
using std::vector;

int Chain1(vector<vector<int>>& cache, const vector<int>& dimensions, int i,
           int j);
int Chain2(const vector<int>& dimensions);

void MatrixChain() {
  vector<int> dimensions{1, 2, 3, 4, 3};

  vector<vector<int>> cache(dimensions.size(),
                            vector<int>(dimensions.size(), -1));
  cout << Chain1(cache, dimensions, 1, dimensions.size() - 1) << endl;
  cout << Chain2(dimensions) << endl;
}

int Chain1(vector<vector<int>>& cache, const vector<int>& dimensions, int i,
           int j) {
  if (i == j) {
    return 0;
  }

  if (cache[i][j] != -1) {
    return cache[i][j];
  }

  int min_ops = INT_MAX;
  for (int k = i; k < j; ++k) {
    min_ops = min(Chain1(cache, dimensions, i, k) +
                      Chain1(cache, dimensions, k + 1, j) +
                      dimensions[i - 1] * dimensions[k] * dimensions[j],
                  min_ops);
  }

  cache[i][j] = min_ops;
  return min_ops;
}

int Chain2(const vector<int>& dimensions) {
  vector<vector<int>> dp(dimensions.size() - 1,
                         vector<int>(dimensions.size() - 1, -1));
  int n = dimensions.size() - 1;

  for (int i = 0; i < n; ++i) {
    dp[i][i] = 0;
  }

  for (int cl = 2; cl <= n; ++cl) {
    // the following loop handle each subsequence that start from i and length
    // is cl.
    for (int i = 0; i <= n - cl; ++i) {
      int j = i + cl - 1;
      dp[i][j] = INT_MAX;
      for (int k = i; k <= j - 1; ++k) {
        dp[i][j] =
            min(dp[i][k] + dp[k + 1][j] +
                    dimensions[i] * dimensions[k + 1] * dimensions[j + 1],
                dp[i][j]);
      }
    }
  }

  return dp[0][n - 1];
}
