#include "heap.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
  MinHeap heap(20);

  heap.InsertKey(3);
  heap.InsertKey(2);
  heap.InsertKey(1);
  heap.InsertKey(15);
  heap.InsertKey(5);
  heap.InsertKey(4);
  heap.InsertKey(45);
  // cout << heap.GetMin() << endl;
  cout << heap.ExtractMin() << endl;
  cout << heap.ExtractMin() << endl;
  cout << heap.ExtractMin() << endl;
  cout << heap.ExtractMin() << endl;
  cout << heap.ExtractMin() << endl;
  cout << heap.ExtractMin() << endl;
  cout << heap.ExtractMin() << endl;
  return 0;
}
