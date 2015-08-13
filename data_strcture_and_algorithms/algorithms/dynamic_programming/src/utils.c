//
// Created by chaomai on 6/17/15.
//

#include "utils.h"

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

void print_two_dim_array(int **array, int dim_1, int dim_2) {
  for (int i = 0; i < dim_1; ++i) {
    for (int j = 0; j < dim_2; ++j) {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
}
