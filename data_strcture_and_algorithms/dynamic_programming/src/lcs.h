//
// Created by chaomai on 6/10/15.
//

#ifndef DATA_STRCTURE_AND_ALGORITHMS_LCS_H
#define DATA_STRCTURE_AND_ALGORITHMS_LCS_H

#include <stdlib.h>
#include <string.h>

#include "utils.h"

int **lcs(char *x, char *y, int m, int n);

char *backtrack(int **d, char *x, char *y, int i, int j);

#endif //DATA_STRCTURE_AND_ALGORITHMS_LCS_H
