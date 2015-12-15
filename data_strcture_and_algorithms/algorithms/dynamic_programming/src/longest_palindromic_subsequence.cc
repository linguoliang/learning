#include "longest_palindromic_subsequence.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;

#include "util.h"

int Lps1(const string &str, int i, int j);
int Lps2(const string &str);
string Lps3(const string &str);

void LongestPalindromicSubsequence() {
  string str("GEEKS FOR GEEKS");
  cout << Lps1(str, 0, str.size() - 1) << endl;
  cout << Lps2(str) << endl;
  cout << Lps3(str) << endl;
  cout << Lps3("GEEKSFORGEEKS") << endl;
}

int Lps1(const string &str, int i, int j) {
  if (i == j) {
    return 1;
  }

  if (str[i] == str[j] & i + 1 == j) {
    return 2;
  }

  if (str[i] == str[j]) {
    return Lps1(str, i + 1, j - 1) + 2;
  }

  return max(Lps1(str, i + 1, j), Lps1(str, i, j - 1));
}

int Lps2(const string &str) {
  int n = str.size();
  vector<vector<int>> dp(n, vector<int>(n, -1));

  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }

  for (int l = 2; l <= n; ++l) {
    // when reach the end of string, j = n - 1, so i + l - 1 = n - 1, hence
    // i = n - l.
    for (int i = 0; i <= n - l; ++i) {
      int j = i + l - 1;

      if (l == 2 && str[i] == str[j]) {
        dp[i][j] = 2;
      } else if (str[i] == str[j]) {
        dp[i][j] = dp[i + 1][j - 1] + 2;
      } else {
        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[0][n - 1];
}

string Lps3(const string &str) {
  int n = str.size();
  vector<vector<int>> dp(n, vector<int>(n, -1));
  vector<vector<int>> way(n, vector<int>(n, -1));

  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
    way[i][i] = 0;
  }

  for (int l = 2; l <= n; ++l) {
    // when reach the end of string, j = n - 1, so i + l - 1 = n - 1, hence
    // i = n - l.
    for (int i = 0; i <= n - l; ++i) {
      int j = i + l - 1;

      if (l == 2 && str[i] == str[j]) {
        dp[i][j] = 2;
        way[i][j] = 0;
      } else if (str[i] == str[j]) {
        dp[i][j] = dp[i + 1][j - 1] + 2;
        way[i][j] = 0;
      } else {
        if (dp[i + 1][j] > dp[i][j - 1]) {
          dp[i][j] = dp[i + 1][j];
          way[i][j] = 1;
        } else {
          dp[i][j] = dp[i][j - 1];
          way[i][j] = 2;
        }
      }
    }
  }

  string result;

  int s = 0;
  int e = n - 1;

  while (s <= e) {
    if (way[s][e] == 0) {
      result.push_back(str[s]);
      ++s;
      --e;
    } else if (way[s][e] == 1) {
      ++s;
    } else {
      --e;
    }
  }

  for (int i = result.size() - 2; i >= 0; --i) {
    result.push_back(result[i]);
  }

  return result;
}
