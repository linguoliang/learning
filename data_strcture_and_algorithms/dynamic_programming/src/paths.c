//
// Created by chaomai on 6/11/15.
//

#include "paths.h"

int paths(int x1, int y1, int x2, int y2) {
  if ((x1 > x2) || (y1 > y2)) {
    return 0;
  }

  int **p = (int **) malloc(sizeof(int *) * (x2 - x1 + 1));

  for (int i = 0; i < y2 - y1 + 1; ++i) {
    p[i] = (int *) malloc(sizeof(int) * (y2 - y1 + 1));
//    int *tmp = p + i;
//    *tmp = (int *) malloc(sizeof(int) * (y2 - y1 + 1));
  }

  for (int i = 0; i < x2 - x1 + 1; ++i) {
    for (int j = 0; j < y2 - y1 + 1; ++j) {
      if ((i == 0) && (j == 0)) {
        p[i][j] = 0;
      } else if (i == 0 || j == 0) {
        p[i][j] = 1;
      } else {
        p[i][j] = p[i - 1][j] + p[i][j - 1];
      }
    }
  }
  print_two_dim_array(p, x2 - x1 + 1, y2 - y1 + 1);
  return p[x2 - x1][y2 - y1];
}
