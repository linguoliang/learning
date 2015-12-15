#include "cutting_rod.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "util.h"

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;

int cut1(const vector<int>& prices, int index, int length);
int cut2(const vector<int>& prices, int length);

void CuttingRod() {
  vector<int> prices{1, 5, 8, 9, 10, 17, 17, 20};
  int length = 8;
  cout << cut1(prices, prices.size(), length) << endl;
  cout << cut2(prices, length) << endl;
}

int cut1(const vector<int>& prices, int n, int length) {
  if (length == 0 || n == 0) {
    return 0;
  }

  if (n > length) {
    return prices[length - 1];
  }

  return max(cut1(prices, n - 1, length),
             cut1(prices, n, length - n) + prices[n - 1]);
}

int cut2(const vector<int>& prices, int length) {
  vector<vector<int>> dp(prices.size() + 1, vector<int>(length + 1, -1));

  for (int i = 0; i <= prices.size(); ++i) {
    for (int j = 0; j <= length; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else if (i > j) {
        dp[i][j] = prices[j - 1];
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - i] + prices[i - 1]);
      }
    }
  }

  vector<int> backint;
  int i = prices.size();
  int j = length;


  for (int p : backint) {
    cout << p << " ";
  }
  cout << endl;

  return dp[prices.size()][length];
}
