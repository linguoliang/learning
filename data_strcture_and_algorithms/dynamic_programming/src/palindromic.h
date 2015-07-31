//
// Created by chaomai on 6/17/15.
//

#ifndef DATA_STRCTURE_AND_ALGORITHMS_PALINDROMIC_H
#define DATA_STRCTURE_AND_ALGORITHMS_PALINDROMIC_H

#include <string.h>
#include <stdlib.h>

#include "utils.h"

int **palindromic(char *str);

char *backtrack_palindromic(int **p, int len);

#endif //DATA_STRCTURE_AND_ALGORITHMS_PALINDROMIC_H
