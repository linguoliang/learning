#include "maximum_sum_increasing_subsequence.h"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#include "util.h"

int maxsum1(const vector<int>& seq, int i, int& max_ref);
int maxsum2(const vector<int>& seq);

void MaximumSumIncreasingSubsequence() {
  vector<int> seq{1, 101, 2, 3, 100, 101, 4, 5};
  int max_sum = 0;
  maxsum1(seq, seq.size() - 1, max_sum);
  cout << max_sum << endl;
  cout << maxsum2(seq) << endl;
}

int maxsum1(const vector<int>& seq, int i, int& max_ref) {
  if (i == 0) {
    return seq[0];
  }

  int cur_max = -1;

  for (int j = 0; j < i; ++j) {
    int sum = maxsum1(seq, j, max_ref);

    if (seq[j] < seq[i] && cur_max < sum + seq[i]) {
      cur_max = sum + seq[i];
    }
  }

  if (cur_max > max_ref) {
    max_ref = cur_max;
  }

  if (cur_max != -1) {
    return cur_max;
  } else {
    return 0;
  }
}

int maxsum2(const vector<int>& seq) {
  vector<int> each_pos_max(seq.size(), -1);
  each_pos_max[0] = 1;

  for (int i = 0; i < seq.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (seq[j] < seq[i] && each_pos_max[i] < each_pos_max[j] + seq[i]) {
        each_pos_max[i] = each_pos_max[j] + seq[i];
      }
    }
  }

  return *max_element(each_pos_max.begin(), each_pos_max.end());
}
