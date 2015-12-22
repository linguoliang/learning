#include "palindrome_partitioning.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <string>

#include "util.h"

using std::cout;
using std::endl;
using std::min;
using std::string;
using std::vector;

int partition1(const string& str, int i, int j);
int partition2(const string& str);
bool isPalidrome(const string& str, int i, int j);

void PalidromePartitioning() {
  string str{"ababbbabbababa"};
  cout << partition1(str, 1, str.size() - 1) << endl;
  cout << partition2(str) << endl;
}

int partition1(const string& str, int i, int j) {
  // the isPalidrome should verify the whole str, not the one without the first
  // element.
  if (i == j || isPalidrome(str, i - 1, j)) {
    return 0;
  }

  int min_cost = INT_MAX;
  for (int k = i; k < j; ++k) {
    min_cost =
        min(partition1(str, i, k) + partition1(str, k + 1, j) + 1, min_cost);
  }

  return min_cost;
}

int partition2(const string& str) {
  vector<vector<int>> dp(str.size(), vector<int>(str.size(), 0));
  int n = str.size();

  for (int i = 0; i < n; ++i) {
    dp[i][i] = 0;
  }

  for (int cl = 2; cl <= n; ++cl) {
    for (int i = 0; i <= n - cl; ++i) {
      int j = i + cl - 1;
      if (isPalidrome(str, i, j)) {
        dp[i][j] = 0;
      } else {
        dp[i][j] = INT_MAX;
        for (int k = i; k <= j - 1; ++k) {
          dp[i][j] = min(dp[i][k] + dp[k + 1][j] + 1, dp[i][j]);
        }
      }
    }
  }

  return dp[0][n - 1];
}

bool isPalidrome(const string& str, int i, int j) {
  while (i < j) {
    if (str[i] != str[j]) {
      return false;
    }

    ++i;
    --j;
  }

  return true;
}
