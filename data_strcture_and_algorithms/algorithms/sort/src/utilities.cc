#include "utilities.h"

void swap(int *a, int *b) {
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

int **new_two_dim_array(int x, int y) {
  int **arr = new int *[x];

  for (int i = 0; i < y; ++i) {
    arr[i] = new int[y];
  }

  return arr;
}
