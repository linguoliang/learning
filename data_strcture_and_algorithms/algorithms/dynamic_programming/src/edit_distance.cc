#include "edit_distance.h"

#include <iostream>
#include <vector>
#include <string>

#include "util.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

int EditDis1(vector<vector<int>> &cache, const string &a, const string &b,
             int m, int n);
int EditDis2(const string &a, const string &b);

void EditDistance() {
  string a("sunday");
  string b("saturday");

  vector<vector<int>> cache(a.size() + 1, vector<int>(b.size() + 1, -1));
  cout << EditDis1(cache, a, b, a.size(), b.size()) << endl;
  cout << EditDis2(a, b) << endl;
}

// m and n is the length, not index
int EditDis1(vector<vector<int>> &cache, const string &a, const string &b,
             int m, int n) {
  if (cache[m][n] != -1) {
    return cache[m][n];
  }

  int ret;
  if (m == 0) {
    ret = n;
  } else if (n == 0) {
    ret = m;
  } else if (a[m - 1] == b[n - 1]) {
    ret = EditDis1(cache, a, b, m - 1,
                   n - 1);  // unnecessary to edit here, go previous location.
  } else {
    ret = min(
        EditDis1(cache, a, b, m, n - 1) +
            1,  // insert b[n] after a, so logically a[m + 1] == b[n]
        EditDis1(cache, a, b, m - 1, n) + 1,       // remove a[m]
        EditDis1(cache, a, b, m - 1, n - 1) + 1);  // substitute b[n] for a[m].
  }

  cache[m][n] = ret;
  return ret;
}

int EditDis2(const string &a, const string &b) {
  vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, -1));

  for (int i = 0; i <= a.size(); ++i) {
    dp[i][0] = i;
  }

  for (int i = 0; i <= b.size(); ++i) {
    dp[0][i] = i;
  }

  for (int i = 1; i <= a.size(); ++i) {
    for (int j = 1; j <= b.size(); ++j) {
      if (a[i] == b[j]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] =
            min(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + 1);
      }
    }
  }

  return dp[a.size()][b.size()];
}
