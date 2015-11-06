#include "longest_common_subsequence.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "util.h"

using std::cout;
using std::endl;
using std::max;
using std::vector;
using std::string;

int Lcs(const string& a, const string& b, int m, int n);
int Lcs1(vector<vector<int>>& cache, const string& a, const string& b, int m,
         int n);
int Lcs2(const string& a, const string& b);
void LcsBacktrack(const vector<vector<int>>& dp, const string& a,
                  const string& b, int m, int n);
void LcsBacktrack2(const vector<vector<int>>& dp, const string& a,
                   const string& b);

void LongestCommonSubsequence() {
  // string a("AGGTAB");
  // string b("GXTXAYB");
  string a("daabeddbcedeabcbcbec");
  string b("daceeaeeaabbabbacedd");

  cout << Lcs(a, b, a.size() - 1, b.size() - 1) << endl;

  vector<vector<int>> cache(a.size(), vector<int>(b.size(), -1));
  cout << Lcs1(cache, a, b, a.size() - 1, b.size() - 1) << endl;

  cout << Lcs2(a, b) << endl;
}

int Lcs(const string& a, const string& b, int m, int n) {
  if (m < 0 || n < 0) {
    return 0;
  }

  if (a[m] == b[n]) {
    return Lcs(a, b, m - 1, n - 1) + 1;
  } else {
    return max(Lcs(a, b, m - 1, n), Lcs(a, b, m, n - 1));
  }
}

int Lcs1(vector<vector<int>>& cache, const string& a, const string& b, int m,
         int n) {
  if (m < 0 || n < 0) {
    return 0;
  }

  if (cache[m][n] != -1) {
    return cache[m][n];
  }

  int ret;
  if (a[m] == b[n]) {
    ret = Lcs1(cache, a, b, m - 1, n - 1) + 1;
  } else {
    ret = max(Lcs1(cache, a, b, m - 1, n), Lcs1(cache, a, b, m, n - 1));
  }

  cache[m][n] = ret;
  return ret;
}

int Lcs2(const string& a, const string& b) {
  // since there is extra row and column (all 0) at beginning.
  vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, -1));

  for (int i = 0; i <= a.size(); ++i) {
    for (int j = 0; j <= b.size(); ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else if (a[i - 1] == b[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  LcsBacktrack(dp, a, b, a.size(), b.size());
  LcsBacktrack2(dp, a, b);
  return dp[a.size()][b.size()];
}

void LcsBacktrack(const vector<vector<int>>& dp, const string& a,
                  const string& b, int m, int n) {
  if (m == 0 || n == 0) {
    return;
  }

  if (a[m - 1] == b[n - 1]) {
    cout << a[m - 1];
    LcsBacktrack(dp, a, b, m - 1, n - 1);
  } else {
    if (dp[m - 1][n] > dp[m][n - 1]) {
      LcsBacktrack(dp, a, b, m - 1, n);
    } else {
      LcsBacktrack(dp, a, b, m, n - 1);
    }
  }
}

void LcsBacktrack2(const vector<vector<int>>& dp, const string& a,
                   const string& b) {
  int i = a.size();
  int j = b.size();

  while (i > 0 && j > 0) {
    if (a[i - 1] == b[j - 1]) {
      cout << a[i - 1];
      --i;
      --j;
    } else {
      if (dp[i - 1][j] > dp[i][j - 1]) {
        --i;
      } else {
        --j;
      }
    }
  }
}
