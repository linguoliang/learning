#include "Second.h"

int main() {
  First f;
  Second s(f);
  s.fun();
  return 0;
}
