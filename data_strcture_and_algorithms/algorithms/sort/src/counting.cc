#include "counting.h"

void counting_sort(int arr[], int n) {
  int count_arr[NUM_RANGE] = {0};
  for (int i = 0; i < n; ++i) {
    ++count_arr[arr[i]];
  }

  for (int i = 1; i < NUM_RANGE - 1; ++i) {
    count_arr[i] += count_arr[i - 1];
  }

  int *tmp = new int[n];
  memcpy(tmp, arr, sizeof(int) * static_cast<size_t>(n));

  for (int i = 0; i < n; ++i) {
    arr[count_arr[tmp[i]] - 1] = tmp[i];
    --count_arr[tmp[i]];
  }

  delete[] tmp;
}
