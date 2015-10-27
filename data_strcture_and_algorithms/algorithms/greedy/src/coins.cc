#include "coins.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::sort;

map<int, int> exchange(vector<int> deno, int num);

map<int, int> exchange(vector<int> deno, int num) {
  sort(deno.begin(), deno.end(), [](int &l, int &r) { return l > r; });

  map<int, int> ret;
  for (auto i = deno.begin(); i != deno.end();) {
    if (num - *i >= 0) {
      if (ret.find(*i) == ret.end()) {
        ret[*i] = 1;
      } else {
        ret[*i] += 1;
      }
      num -= *i;
    } else {
      ++i;
    }
  }

  return ret;
}

void coins() {
  vector<int> deno({1, 2, 5, 10, 20, 50, 100, 500, 1000});
  auto res = exchange(deno, 999);
  for (auto d : deno) {
    if (res[d] != 0) {
      cout << d << ": " << res[d] << endl;
    }
  }
}
