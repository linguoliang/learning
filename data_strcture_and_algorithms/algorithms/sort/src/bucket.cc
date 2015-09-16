#include "bucket.h"

void bucket_sort(double arr[], int n) {
  vector<double> **bucket = new vector<double> *[n];

  for (int i = 0; i < BUCKET_SIZE; ++i) {
    bucket[i] = new vector<double>(0);
  }

  for (int i = 0; i < n; ++i) {
    bucket[static_cast<int>(BUCKET_SIZE * arr[i])]->push_back(arr[i]);
  }

  for (int i = 0; i < BUCKET_SIZE; ++i) {
    sort(bucket[i]->begin(), bucket[i]->end());
  }

  for (int i = 0, j = 0; i < BUCKET_SIZE; ++i) {
    for (auto b = bucket[i]->begin(); b != bucket[i]->end(); ++b) {
      arr[j] = *b;
      ++j;
    }
  }
}
