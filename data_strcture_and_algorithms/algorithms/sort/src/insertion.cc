#include "insertion.h"

void insertion_sort(int arr[], int n) {
  for (int i = 1; i < n; ++i) {
    int cur_val = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > cur_val) {
      arr[j + 1] = arr[j];
      --j;
    }
    // when the while loop ends, the j is at the position which is before the
    // moved one.
    // ...k-1, k, k+1... and k->k+1
    //     ^
    //     j
    arr[j + 1] = cur_val;
  }
}
