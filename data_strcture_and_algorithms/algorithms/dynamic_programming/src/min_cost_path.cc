#include "min_cost_path.h"

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::min;
using std::vector;

int MinPath(const vector<vector<int>>& grid, vector<vector<int>>& cache,
            size_t i, size_t j);

void MinCostPath() {
  vector<vector<int>> grid{{1, 2, 3, 4}, {4, 8, 2, 1}, {1, 5, 3, 10}};
  vector<vector<int>> cache(grid.size(), vector<int>(grid.front().size(), -1));
  cout << MinPath(grid, cache, grid.size() - 1, grid.front().size() - 1)
       << endl;
}

int MinPath(const vector<vector<int>>& grid, vector<vector<int>>& cache,
            size_t i, size_t j) {
  if (cache[i][j] != -1) {
    return cache[i][j];
  }

  int ret;
  if (i == 0 && j == 0) {
    ret = grid[i][j];
  } else if (i == 0 && j != 0) {
    ret = MinPath(grid, cache, i, j - 1) + grid[i][j];
  } else if (j == 0 && i != 0) {
    ret = MinPath(grid, cache, i - 1, j) + grid[i][j];
  } else {
    ret = min(MinPath(grid, cache, i - 1, j) + grid[i][j],
              MinPath(grid, cache, i, j - 1) + grid[i][j]);
  }

  cache[i][j] = ret;
  return ret;
}
