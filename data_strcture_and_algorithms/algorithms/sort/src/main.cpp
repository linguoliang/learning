#include "selection.h"
#include "utilities.h"

int main(void) {
  int arr[] = {64, 25, 12, 22, 11, 11};
  int n = sizeof(arr) / sizeof(arr[0]);
  selection_sort(arr, n);
  print_array(arr, n);
  return 0;
}
