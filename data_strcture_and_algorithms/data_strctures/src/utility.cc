#include "utility.h"

namespace utility {
void Swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}
}
