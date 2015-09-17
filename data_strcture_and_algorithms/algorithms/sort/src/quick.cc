//                                                               +----->pivot
//               ij                                              +
//                                                               x
//                +----------------------------------------------+
//                p                                              r
//
//
//
//                         i                    j                x
//                +----------------------------------------------+
//                p                                              r
//                +---+----+
//                    |
//                    v     +--------+----------+
//                 (<= x)            |
//                                   v
//                                 (> x)
//
//                                                               j
//                                    i                          x
// end of loop:   +----------------------------------------------+
//                 p                                             r
//
//                                     +------------+------------+
//                                                  |
//                                                  v
//                                            swap a[i+1] and a[r]

#include "quick.h"

int q_partition(int arr[], int p, int r);

void q_sort(int arr[], int p, int r);

void quick_sort(int arr[], int n) { q_sort(arr, 0, n - 1); }

int q_partition(int arr[], int p, int r) {
  int x = arr[r];
  int i = p - 1;

  for (int j = p; j < r; ++j) {
    if (arr[j] <= x) {
      ++i;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[r]);

  return i + 1;
}

void q_sort(int arr[], int p, int r) {
  if (p < r) {
    int q = q_partition(arr, p, r);
    q_sort(arr, p, q - 1);
    q_sort(arr, q + 1, r);
  }
}
