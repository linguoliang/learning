#include "coin_change.h"

#include <iostream>
#include <vector>

#include "util.h"

using std::cout;
using std::endl;
using std::vector;

int Change1(vector<vector<int>>& cache, const vector<int>& coins, int n, int m);
int Change2(const vector<int>& coins, int n);

void CoinChange() {
  vector<int> coins{3, 1, 2, 4};
  int n = 4;

  vector<vector<int>> cache(n + 1, vector<int>(coins.size(), -1));
  cout << Change1(cache, coins, n, coins.size() - 1) << endl;
  cout << Change2(coins, n) << endl;
}

int Change1(vector<vector<int>>& cache, const vector<int>& coins, int n,
            int m) {
  if (n == 0) {
    return 1;
  }

  if (n < 0) {
    return 0;
  }

  // no coins to use
  if (n > 0 && m < 0) {
    return 0;
  }

  if (cache[n][m] != -1) {
    return cache[n][m];
  }

  int ret;
  // two sets of subproblems:
  // set contains coins[m],
  // set doesn't contains coins[m].
  ret =
      Change1(cache, coins, n - coins[m], m) + Change1(cache, coins, n, m - 1);

  cache[n][m] = ret;
  return ret;
}

int Change2(const vector<int>& coins, int n) {
  int m = coins.size();
  vector<vector<int>> dp(n + 1, vector<int>(m, -1));

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0) {
        dp[i][j] = 1;
      } else if (j == 0) {
        // when j == 0, dp[i][j] cannot simply be 0 or 1.
        // because the one coin may be valid if t * coins[j] == i.
        if (i % coins[j] == 0) {
          dp[i][j] = 1;
        } else {
          dp[i][j] = 0;
        }
      } else if (i < coins[j]) {
        // because there is a i - coins[j] in the last case.
        dp[i][j] = dp[i][j - 1];
      } else {
        dp[i][j] = dp[i - coins[j]][j] + dp[i][j - 1];
      }
    }
  }

  return dp[n][m];
}
