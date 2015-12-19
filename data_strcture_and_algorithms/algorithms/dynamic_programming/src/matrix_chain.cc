#include "matrix_chain.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using std::min;
using std::cout;
using std::endl;
using std::vector;

int Chain1(vector<vector<int>>& cache, const vector<int>& dimensions, int i,
           int j);
int Chain2(const vector<int>& dimensions);

void MatrixChain() {
  vector<int> dimensions{1,  2,  3,  4,  3,  1,  2,   3,   4,   5,   6,  7,  8,
                         9,  10, 11, 12, 13, 14, 15,  16,  17,  18,  19, 20, 21,
                         22, 23, 24, 25, 26, 27, 28,  29,  30,  31,  32, 33, 34,
                         35, 36, 37, 38, 39, 40, 296, 297, 298, 299, 300};

  vector<vector<int>> cache(dimensions.size(),
                            vector<int>(dimensions.size(), -1));
  cout << Chain1(cache, dimensions, 1, dimensions.size() - 1) << endl;
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
  vector<vector<int>> dp(dimensions.size(), vector<int>(dimensions.size(), -1));
}
