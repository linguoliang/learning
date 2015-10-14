#include "chpater4.h"

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

void chpater4() {
  for (int i = 0; i != 100; ++i) {
    cout << i << setw(10) << i * i << endl;
  }
}
