#include "insertion.h"

void insertion_sort(int arr[], int n) {
  for (int i = 1; i != n; ++i) {
    int cur_val = arr[i];

    int j;
    for (j = i; j >= 1 && arr[j - 1] > cur_val; --j) {
      arr[j] = arr[j - 1];
    }
    arr[j] = cur_val;
  }
}
