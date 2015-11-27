#include "knapsack.h"

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::vector;

struct item {
  int value;
  int weight;
};

int packet1(vector<vector<int>>& cache, const vector<item>& items, int w,
            int n);
int packet2(const vector<item>& items, int w);

void Knapsack() {
  vector<item> items{{12, 12}, {3, 3}, {7, 7}, {4, 4}, {5, 5}, {13, 12}, {2, 2},
                     {8, 8},   {4, 4}, {7, 7}, {6, 6}, {5, 5}, {7, 7}};
  int w = 90;

  vector<vector<int>> cache(w + 1, vector<int>(items.size(), -1));
  cout << packet1(cache, items, w, items.size() - 1) << endl;
  cout << packet2(items, w) << endl;
}

int packet1(vector<vector<int>>& cache, const vector<item>& items, int w,
            int n) {
  if (w == 0 || n < 0) {
    return 0;
  }

  if (cache[w][n] != -1) {
    return cache[w][n];
  }

  int ret;
  if (items[n].weight > w) {
    ret = packet1(cache, items, w, n - 1);
  } else {
    ret =
        max(packet1(cache, items, w - items[n].weight, n - 1) + items[n].value,
            packet1(cache, items, w, n - 1));
  }
  cache[w][n] = ret;
  return cache[w][n];
}

int packet2(const vector<item>& items, int w) {
  int n = items.size();
  vector<vector<int>> dp(w + 1, vector<int>(items.size() + 1, -1));

  for (int i = 0; i <= w; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else if (items[j - 1].weight > i) {
        dp[i][j] = dp[i][j - 1];
      } else {
        dp[i][j] = max(dp[i - items[j - 1].weight][j - 1] + items[j - 1].value,
                       dp[i][j - 1]);
      }
    }
  }

  return dp[w][n];
}
