#ifndef HEAP_H_
#define HEAP_H_

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::memmove;
using std::swap;

class MinHeap {
 public:
  explicit MinHeap(size_t capacity) {
    size_ = 0;
    capacity_ = capacity;
    arr_ = new int[capacity_];
  }

  ~MinHeap() { delete[] arr_; }

  int ExtractMin();
  int GetMin() { return arr_[0]; }
  void DeleteKey(int k);
  void InsertKey(int k);

 private:
  void AdjustKeyUp(int i);
  void DecreaseKey(int k, int new_val);
  void MinHeapify(int i);
  int Parent(int i) { return (i - 1) / 2; }
  int Left(int i) { return 2 * i + 1; }
  int Right(int i) { return 2 * i + 2; }

  int *arr_;
  size_t capacity_;
  size_t size_;
};

#endif
