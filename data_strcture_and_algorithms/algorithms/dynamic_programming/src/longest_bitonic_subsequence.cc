#include "longest_bitonic_subsequence.h"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int bitonic1(const vector<int> &seq);
int Lis(const vector<int> &seq, vector<int> &is, int i);
int Lds(const vector<int> &seq, vector<int> &ds, int i);
int bitonic2(const vector<int> &seq);

void LongestBitonicSubsequence() {
  // vector<int> seq{1, 11, 2, 10, 4, 5, 2, 1};
  vector<int> seq{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
  cout << bitonic1(seq) << endl;
  cout << bitonic2(seq) << endl;
}

int bitonic1(const vector<int> &seq) {
  vector<int> is(seq.size(), -1);
  vector<int> ds(seq.size(), -1);
  Lis(seq, is, seq.size() - 1);
  Lds(seq, ds, 0);

  int max_bitoic = -1;
  for (int i = 0; i < seq.size(); ++i) {
    if (is[i] + ds[i] - 1 > max_bitoic) {
      max_bitoic = is[i] + ds[i] - 1;
    }
  }

  return max_bitoic;
}

int Lis(const vector<int> &seq, vector<int> &is, int i) {
  if (is[i] != -1) {
    return is[i];
  }

  int ret;
  if (i == 0) {
    ret = 1;
  }

  int cur_max = -1;

  for (int j = 0; j < i; ++j) {
    int len = Lis(seq, is, j);

    if (seq[j] < seq[i] && cur_max < len + 1) {
      cur_max = len + 1;
    }
  }

  if (cur_max != -1) {
    ret = cur_max;
  } else {
    ret = 1;
  }

  is[i] = ret;
  return ret;
}

int Lds(const vector<int> &seq, vector<int> &ds, int i) {
  if (ds[i] != -1) {
    return ds[i];
  }

  int ret;
  if (i == 0) {
    ret = 1;
  }

  int cur_max = -1;

  for (int j = seq.size() - 1; j > i; --j) {
    int len = Lds(seq, ds, j);

    if (seq[j] < seq[i] && cur_max < len + 1) {
      cur_max = len + 1;
    }
  }

  if (cur_max != -1) {
    ret = cur_max;
  } else {
    ret = 1;
  }

  ds[i] = ret;
  return ret;
}

int bitonic2(const vector<int> &seq) {
  vector<int> is(seq.size(), 1);
  vector<int> is_prev(seq.size(), -1);
  vector<int> ds(seq.size(), 1);
  vector<int> ds_prev(seq.size(), -1);

  is[0] = 1;
  for (int i = 0; i < seq.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (seq[j] < seq[i] && is[i] < is[j] + 1) {
        is[i] = is[j] + 1;
        is_prev[i] = j;
      }
    }
  }

  ds[seq.size() - 1] = 1;
  for (int i = seq.size() - 1; i >= 0; --i) {
    for (int j = seq.size() - 1; j > i; --j) {
      if (seq[j] < seq[i] && ds[i] < ds[j] + 1) {
        ds[i] = ds[j] + 1;
        ds_prev[i] = j;
      }
    }
  }

  int max_bitoic = -1;
  int max_index = -1;
  for (int i = 0; i < seq.size(); ++i) {
    if (max_bitoic < is[i] + ds[i] - 1) {
      max_bitoic = is[i] + ds[i] - 1;
      max_index = i;
    }
  }

  for (int i = max_index; i != -1; i = is_prev[i]) {
    cout << seq[i] << " ";
  }

  for (int i = ds_prev[max_index]; i != -1; i = ds_prev[i]) {
    cout << seq[i] << " ";
  }

  return max_bitoic;
}
