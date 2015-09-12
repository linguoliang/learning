#include "bubble.h"
#include "heap.h"
#include "insertion.h"
#include "selection.h"
#include "merge.h"
#include "utilities.h"

int main(void) {
  int arr[] = {64, 25, 12, 23, 12, 11, 2, 6};
  // int arr[] = {1, 4, 3, 2};

  int n = sizeof(arr) / sizeof(arr[0]);
  // bubble_sort(arr, n);
  heap_sort(arr, n);
  // insertion_sort(arr, n);
  // merge_sort(arr, n);
  // selection_sort(arr, n);
  print_array(arr, n);
  return 0;
}
