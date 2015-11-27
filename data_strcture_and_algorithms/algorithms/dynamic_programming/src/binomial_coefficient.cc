#include "binomial_coefficient.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include "util.h"

using std::cout;
using std::endl;
using std::min;
using std::vector;

int Coefficient1(vector<vector<long>>& cache, int n, int k);
int Coefficient2(int n, int k);

void BinomialCoefficient() {
  int n = 5;
  int k = 2;

  vector<vector<long>> cache(n + 1, vector<long>(k + 1, -1));
  cout << Coefficient1(cache, n, k) << endl;
  cout << Coefficient2(n, k) << endl;
}

int Coefficient1(vector<vector<long>>& cache, int n, int k) {
  if (n == k || k == 0) {
    return 1;
  }

  if (cache[n][k] != -1) {
    return cache[n][k];
  }

  int ret = Coefficient1(cache, n - 1, k - 1) + Coefficient1(cache, n - 1, k);
  cache[n][k] = ret;
  return ret;
}

int Coefficient2(int n, int k) {
  vector<vector<long>> dp(n + 1, vector<long>(k + 1, -1));

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      // attention
      // the case of j > i is important, since C(2, 5) is 0 in mathematics and
      // has no meaning in reality.
      if (j > i) {
        dp[i][j] = 0;
      } else if (i == j || j == 0) {
        dp[i][j] = 1;
      } else {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      }
    }
  }

  return dp[n][k];
}
