#include "word_wrap.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

#include "util.h"

using std::cout;
using std::endl;
using std::min;
using std::vector;

// Cost of a line = (Number of extra spaces in the line)^3
// Total Cost = Sum of costs for all lines

int Wrap1(const vector<int>& words, int m, int i);
int Wrap2(const vector<int>& words, int m, int i);

void WordWrap() {
  // vector<int> words{3, 1, 2, 2, 1, 3, 2, 5};
  vector<int> words{3, 2, 2, 5};
  int m = 6;
  cout << Wrap1(words, m, 0) << endl;
}

int Wrap1(const vector<int>& words, int m, int i) {
  if (i == words.size()) {
    return 0;
  }

  int min_cost = INT_MAX;
  int len = 0;

  for (int j = 0; j < words.size(); ++j) {
    len += words[i + j] + 1;

    if (len > m) {
      break;
    } else {
      min_cost = min(
          Wrap1(words, m, i + j + 1) + static_cast<int>(pow(m - len + 1, 3.0)),
          min_cost);
    }
  }

  return min_cost;
}

int Wrap2(const vector<int>& words, int m, int i) {}
