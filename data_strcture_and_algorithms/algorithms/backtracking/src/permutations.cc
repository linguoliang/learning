#include "permutations.h"

void Permute(string& str, string::size_type l);

void Permutations(string str) { Permute(str, 0); }

void Permute(string& str, string::size_type l) {
  string::size_type s = str.size();

  if (l == s) {
    cout << str << endl;
    return;
  }

  for (string::size_type i = l; i != s; ++i) {
    swap(str[l], str[i]);
    Permute(str, l + 1);
    swap(str[l], str[i]);
  }
}
