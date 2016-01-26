#include "WordCount.h"

int main() {
  int d = 1;
  const void *pd = &d;
  int *p = const_cast<int *>(pd);

  return 0;
}