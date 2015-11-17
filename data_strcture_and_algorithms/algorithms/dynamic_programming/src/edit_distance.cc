#include "edit_distance.h"

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#include "util.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::tuple;

int EditDis1(vector<vector<int>> &cache, const string &a, const string &b,
             int m, int n);
int EditDis2(const string &a, const string &b);
void EditDisBacktrack(const vector<vector<int>> &dp, const string &a,
                      const string &b, int m, int n);

void EditDistance() {
  string a("sunday");
  string b("saturday");

  cout << "a: " << a << " ,b:" << b << endl;
  vector<vector<int>> cache(a.size(), vector<int>(b.size(), -1));
  cout << EditDis1(cache, a, b, a.size() - 1, b.size() - 1) << endl;
  // PrintArray(cache);
  cout << EditDis2(a, b) << endl;
}

// m and n are index
int EditDis1(vector<vector<int>> &cache, const string &a, const string &b,
             int m, int n) {
  // pay attention to these special return condition.
  // don't simply use a statement like
  // if(m < 0) return m; else if(n < 0) return n;
  if (m < 0 && n < 0) {
    return 0;
  } else if (m < 0 && n >= 0) {
    return n;
  } else if (m >= 0 && n < 0) {
    return m;
  }

  if (cache[m][n] != -1) {
    return cache[m][n];
  }

  int ret;
  if (a[m] == b[n]) {
    ret =
        EditDis1(cache, a, b, m - 1,
                 n - 1);  // unnecessary to edit here, go to previous location.
  } else {
    ret = min(
        EditDis1(cache, a, b, m, n - 1) + 1,       // insert b[n] after a
        EditDis1(cache, a, b, m - 1, n) + 1,       // remove a[m]
        EditDis1(cache, a, b, m - 1, n - 1) + 1);  // substitute b[n] for a[m]
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

  // PrintArray(dp);
  EditDisBacktrack(dp, a, b, a.size(), b.size());
  return dp[a.size()][b.size()];
}

void EditDisBacktrack(const vector<vector<int>> &dp, const string &a,
                      const string &b, int m, int n) {
  if (m <= 0 || n <= 0) {
    return;
  }

  if (a[m - 1] == b[n - 1]) {
    cout << b[n - 1] << " at " << n - 1 << " in b "
         << " are same." << endl;
    EditDisBacktrack(dp, a, b, m - 1, n - 1);
    // since suitable solution is found, just directly return;
    return;
  }

  int insert_v = dp[m][n - 1] + 1;
  int remove_v = dp[m - 1][n] + 1;
  int substitute_v = dp[m - 1][n - 1] + 1;

  int min_value;
  int min_index;

  if (insert_v < remove_v) {
    min_value = insert_v;
    min_index = 0;
  } else {
    min_value = remove_v;
    min_index = 1;
  }

  if (substitute_v < min_value) {
    min_value = substitute_v;
    min_index = 2;
  }

  switch (min_index) {
    case 0: {
      cout << "insert " << b[n - 1] << " at " << m << " in a" << endl;
      EditDisBacktrack(dp, a, b, m, n - 1);
      break;
    }
    case 1: {
      cout << "remove " << a[m - 1] << " at " << m - 1 << " in a" << endl;
      EditDisBacktrack(dp, a, b, m - 1, n);
      break;
    }
    case 2: {
      cout << "substitute " << b[n - 1] << " at " << n - 1 << " in b "
           << " for " << a[m - 1] << " at " << n - 1 << " in a" << endl;
      EditDisBacktrack(dp, a, b, m - 1, n - 1);
      break;
    }
  }
}
