//
// Created by chaomai on 6/17/15.
//

#include "coins.h"

int *coins(int *denominations, int num, int sum) {
  int *c = (int *) malloc(sizeof(int) * (sum + 1));

  for (int i = 0; i <= sum; ++i) {
    c[i] = INT_MAX;
  }
  c[0] = 0;

  for (int i = 0; i <= sum; ++i) {
    for (int j = 0; j < num; ++j) {
      if (denominations[j] <= i) {
        c[i] = min(1 + c[i - denominations[j]], c[i]);
      }
    }
  }
  return c;
}
