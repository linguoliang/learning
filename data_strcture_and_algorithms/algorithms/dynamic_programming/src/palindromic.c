//
// Created by chaomai on 6/17/15.
//

#include "palindromic.h"

int **palindromic(char *str) {
  int len = strlen(str);

  int **p = (int **) malloc(sizeof(int *) * len);

  for (int i = 0; i < len; ++i) {
    p[i] = (int *) malloc(sizeof(int) * len);
//    int *tmp = p + i;
//    *tmp = (int *) malloc(sizeof(int) * len);
  }

  for (int i = 0; i < len; ++i) {
    for (int j = i; j < len; ++j) {
      if (i == 0) {
        p[j - i][j] = 1;
      } else if (i == 1) {
        if (str[j - i] == str[j]) {
          p[j - i][j] = 2;
        } else {
          p[j - i][j] = 1;
        }
      } else {
        if (str[j - i] == str[j]) {
          p[j - i][j] = p[j - i + 1][j - 1] + 2;
        } else {
          p[j - i][j] = max(p[j - i + 1][j], p[j - i][j + 1]);
        }
      }
    }
  }

  print_two_dim_array(p, len, len);
  return p;
}

char *backtrack_palindromic(int **p, int len) {

}
