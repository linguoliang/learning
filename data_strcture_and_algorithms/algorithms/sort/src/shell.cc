#include "shell.h"

void shell_sort(int arr[], int n) {
  // using shell gap sequence
  for (int gap = n; gap > 0; gap /= 2) {
    for (int i = gap; i != n; ++i) {
      int cur_val = arr[i];

      int j;
      for (j = i; j >= gap && arr[j - gap] > cur_val; j -= gap) {
        arr[j] = arr[j - gap];
      }
      arr[j] = cur_val;
    }
  }
}
