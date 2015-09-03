#include "selection.h"

void selection_sort(int arr[], int n) {
  // the minimum value of the last is itself, so it's uncessary to reach it.
  // for (int i = 0; i < n - 1; i++) {
  for (int i = 0; i < n; i++) {
    int min_index = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[min_index] > arr[j]) {
        min_index = j;
      }
    }
    swap(&arr[i], &arr[min_index]);
  }
}
