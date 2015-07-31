//
// Created by chaomai on 6/10/15.
//

#include "lcs.h"

//char *backtrack(int **d, char *x, char *y, int i, int j) {
//  char *str = (char *) malloc(sizeof(char) * 50);
//  memset(str, 0, 50);
//  if (i == 0 || j == 0) {
//    return str;
//  } else if (x[i] == y[j]) {
//    return strncat(backtrack(d, x, y, i - 1, j - 1), x + i, 1);
//  } else if (d[i - 1][j] > d[i][j - 1]) {
//    backtrack(d, x, y, i - 1, j);
//  } else {
//    backtrack(d, x, y, i, j - 1);
//  }
//}

int **lcs(char *x, char *y, int m, int n) {
  int **d = (int **) malloc(sizeof(int *) * (m + 1));

  for (int i = 0; i < m + 1; ++i) {
    d[i] = (int *) malloc(sizeof(int) * (n + 1));
//    int *tmp = d + i;
//    *tmp = (int *) malloc(sizeof(int) * (n + 1));
  }

  for (int i = 0; i < m + 1; ++i) {
    for (int j = 0; j < n + 1; ++j) {
      if (i == 0 || j == 0) {
        d[i][j] = 0;
      } else if (x[i] == y[j]) {
        d[i][j] = d[i - 1][j - 1] + 1;
      } else {
        d[i][j] = max(d[i][j - 1], d[i - 1][j]);
      }
    }
  }

  return d;
}
