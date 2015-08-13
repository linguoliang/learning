//
// Created by chaomai on 6/3/15.
//

#include "lcs.h"
#include "paths.h"
#include "coins.h"
#include "palindromic.h"
#include "robber.h"

void test_lcs(void);
void test_paths(void);
void test_coins(void);
void test_robber(void);
void test_palindromic(void);

int main() {
 test_lcs();
/*  test_paths(); */
/*  test_coins(); */
/*  test_robber(); */
  return 0;
}

void test_lcs() {
  char *x = "abcbdab";
  char *y = "bdcaba";
  size_t len_x = strlen(x);
  size_t len_y = strlen(y);
  int **d = lcs(x, y, (int) len_x, (int) len_y);
  printf("%d", d[len_x][len_y]);
  //printf("%s", backtrack(d, x, y, len_x, len_y));
}

void test_paths() {
  printf("%d", paths(1, 2, 7, 9));
}

void test_coins() {
  int denominations[5] = {1, 3, 5, 7, 9};
  int sum = 20;
  int *c = coins(denominations, 5, sum);
  for (int i = 0; i < sum; ++i) {
    printf("%d ", c[i]);
  }
}

void test_palindromic() {
  palindromic("acecc");
}

void test_robber() {
  int n = 5;
  int a[5] = {1, 2, 3, 5, 7};
  printf("%d", rob(a, n));
}
