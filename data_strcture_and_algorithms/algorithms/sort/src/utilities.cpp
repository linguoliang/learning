#include "utilities.h"

void swap(int *a, int *b) {
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

void print_array(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}
