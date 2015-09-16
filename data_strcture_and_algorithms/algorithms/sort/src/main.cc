#include "bubble.h"
#include "bucket.h"
#include "counting.h"
#include "heap.h"
#include "insertion.h"
#include "merge.h"
#include "quick.h"
#include "selection.h"
#include "shell.h"
#include "utilities.h"

void bucket_test();

int main(void) {
  int arr[] = {64, 25, 12, 23, 12, 11, 2, 6};
  // int arr[] = {1, 4, 3, 2, 0};

  int n = sizeof(arr) / sizeof(arr[0]);
  // bubble_sort(arr, n);
  // bucket_test();
  // counting_sort(arr, n);
  // heap_sort(arr, n);
  // insertion_sort(arr, n);
  // merge_sort(arr, n);
  quick_sort(arr, n);
  // selection_sort(arr, n);
  // shell_sort(arr, n);
  print_array(arr, n);
  return 0;
}

void bucket_test() {
  double arr[] = {0.64, 0.25, 0.12, 0.23, 0.12, 0.11, 0.2, 0.6};
  int n = sizeof(arr) / sizeof(arr[0]);
  bucket_sort(arr, n);
  print_array(arr, n);
}
