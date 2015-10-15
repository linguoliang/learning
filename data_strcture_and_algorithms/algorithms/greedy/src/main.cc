#include "activity_selection.h"
#include "huffman_coding.h"

#include <iostream>

using std::cout;
using std::endl;

void huffman_coding();

int main() {
  // activity_selection();
  huffman_coding();
  return 0;
}

void huffman_coding() {
  HuffmanCode hc({{'a', 5},
                  {'b', 9},
                  {'c', 12},
                  {'d', 13},
                  {'e', 16},
                  {'f', 45}});

  cout << "a: " << hc.get_code('a') << endl;
  cout << "b: " << hc.get_code('b') << endl;
  cout << "c: " << hc.get_code('c') << endl;
  cout << "d: " << hc.get_code('d') << endl;
  cout << "e: " << hc.get_code('e') << endl;
  cout << "f: " << hc.get_code('f') << endl;
}
