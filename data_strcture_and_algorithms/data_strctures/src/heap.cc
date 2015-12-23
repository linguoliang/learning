#include "heap.h"

int MinHeap::ExtractMin() {
  if (size_ <= 0) {
    return INT_MAX;
  }

  if (size_ == 1) {
    size_--;
    return GetMin();
  }

  int min = GetMin();
  arr_[0] = arr_[size_ - 1];
  size_--;
  MinHeapify(0);
  return min;
}

void MinHeap::DeleteKey(int i) {
  DecreaseKey(i, INT_MIN);
  ExtractMin();
}

void MinHeap::InsertKey(int k) {
  if (size_ == capacity_) {
    cout << endl
         << "Overflow: Could not insert key" << endl;
    return;
  }

  size_++;
  int i = static_cast<int>(size_ - 1);
  arr_[i] = k;
  AdjustKeyUp(i);
}

void MinHeap::AdjustKeyUp(int i) {
  while (i != 0 && arr_[Parent(i)] > arr_[i]) {
    swap(arr_[Parent(i)], arr_[i]);
    i = Parent(i);
  }
}

void MinHeap::DecreaseKey(int i, int new_val) {
  arr_[i] = new_val;
  AdjustKeyUp(i);
}

void MinHeap::MinHeapify(int i) {
  int l = Left(i);
  int r = Right(i);

  int smallest = i;
  if (static_cast<size_t>(l) < size_ && arr_[l] < arr_[i]) {
    smallest = l;
  }

  if (static_cast<size_t>(r) < size_ && arr_[r] < arr_[smallest]) {
    smallest = r;
  }

  if (smallest != i) {
    swap(arr_[smallest], arr_[i]);
    MinHeapify(smallest);
  }
}
