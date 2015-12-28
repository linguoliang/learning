#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;

int DFSUtil(int x, int y, const vector<vector<int>>& m,
            vector<vector<int>>& dp);

int main() {
  fstream fs;
  fs.open("A-large-practice.in", fstream::in);

  int n;
  fs >> n;

  for (int i = 0; i < n; ++i) {
    int c;
    fs >> c;
    vector<vector<int>> m(c, vector<int>(c, 0));

    // read each map
    for (int j = 0; j < c; ++j) {
      for (int k = 0; k < c; ++k) {
        fs >> m[j][k];
      }
    }

    // process each map
    vector<vector<int>> dp(c, vector<int>(c, 0));

    int maxSteps = INT_MIN;
    int pos = INT_MAX;

    for (int j = 0; j < c; ++j) {
      for (int k = 0; k < c; ++k) {
        int steps = DFSUtil(j, k, m, dp);
        if (steps > maxSteps) {
          maxSteps = steps;
          pos = m[j][k];
        } else if (steps == maxSteps) {
          if (pos > m[j][k]) {
            pos = m[j][k];
          }
        }
      }
    }

    cout << "Case #" << i + 1 << ": " << pos << " " << maxSteps << endl;
  }
  return 0;
}

int DFSUtil(int x, int y, const vector<vector<int>>& m,
            vector<vector<int>>& dp) {
  if (dp[x][y] != 0) {
    return dp[x][y];
  }

  // check and move to four directions
  vector<vector<int>> direct{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
  for (int i = 0; i < 4; ++i) {
    int nx = x + direct[i][0];
    int ny = y + direct[i][1];

    if (nx >= 0 && nx < dp.size() && ny >= 0 && ny < dp.size() &&
        m[nx][ny] == m[x][y] + 1) {
      dp[x][y] = DFSUtil(nx, ny, m, dp) + 1;
      return dp[x][y];
    }
  }

  dp[x][y] = 1;
  return dp[x][y];
}
