#include "utilities.h"

int **NewTwoDimArray(int x, int y) {
  int **arr = new int *[x];

  for (int i = 0; i < y; ++i) {
    arr[i] = new int[y];
  }

  return arr;
}
