#ifndef HUFFMAN_CODING_H_
#define HUFFMAN_CODING_H_

#include <algorithm>
#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

template <typename T>
class MinHeap {
 public:
  explicit MinHeap();
  explicit MinHeap(const std::vector<T> &arr);
  ~MinHeap();

  void DecreseKey(typename std::vector<T>::size_type idx, T key);
  void InsertKey(T key);
  T ExtractMin();
  T get_min() { return arr_[0]; }

  typename std::vector<T>::size_type size() { return arr_.size(); }
  typename std::vector<T>::size_type capacity() { return arr_.capacity(); }

 private:
  void BuildMinHeap();
  void MinHeapify(typename std::vector<T>::size_type idx);
  typename std::vector<T>::size_type parent(
      typename std::vector<T>::size_type idx) {
    return (idx - 1) / 2;
  }
  typename std::vector<T>::size_type left(
      typename std::vector<T>::size_type idx) {
    return 2 * idx + 1;
  }
  typename std::vector<T>::size_type right(
      typename std::vector<T>::size_type idx) {
    return 2 * idx + 2;
  }

  std::vector<T> arr_;
};

template <typename T>
MinHeap<T>::MinHeap() {}

template <typename T>
MinHeap<T>::MinHeap(const std::vector<T> &arr) {
  arr_ = arr;
  BuildMinHeap();
}

template <typename T>
MinHeap<T>::~MinHeap() {}

template <typename T>
void MinHeap<T>::DecreseKey(typename std::vector<T>::size_type idx, T key) {
  arr_[idx] = key;

  while (idx != 0 && arr_[parent(idx)] > arr_[idx]) {
    std::swap(arr_[parent(idx)], arr_[idx]);
    idx = parent(idx);
  }
}

template <typename T>
void MinHeap<T>::InsertKey(T key) {
  arr_.push_back(key);
  DecreseKey(size() - 1, key);
}

template <typename T>
T MinHeap<T>::ExtractMin() {
  T ret = get_min();
  arr_[0] = arr_[size() - 1];
  arr_.erase(arr_.begin() + static_cast<long>(size()) - 1);
  MinHeapify(0);
  return ret;
}

template <typename T>
void MinHeap<T>::BuildMinHeap() {
  for (int i = static_cast<int>(size() - 1) / 2; i >= 0; --i) {
    MinHeapify(static_cast<typename std::vector<T>::size_type>(i));
  }
}

template <typename T>
void MinHeap<T>::MinHeapify(typename std::vector<T>::size_type idx) {
  auto smalleat_idx = idx;

  if (left(idx) < size() && arr_[left(idx)] < arr_[idx]) {
    smalleat_idx = left(idx);
  }

  if (right(idx) < size() && arr_[right(idx)] < arr_[smalleat_idx]) {
    smalleat_idx = right(idx);
  }

  if (smalleat_idx != idx) {
    std::swap(arr_[smalleat_idx], arr_[idx]);
    MinHeapify(smalleat_idx);
  }
}

struct HuffmanNode {
  char data;
  int freq;
  struct HuffmanNode *left;
  struct HuffmanNode *right;

  HuffmanNode(char d, int f, struct HuffmanNode *l, struct HuffmanNode *r)
      : data(d), freq(f), left(l), right(r) {}
  HuffmanNode(char d, int f)
      : data(d), freq(f), left(nullptr), right(nullptr) {}
  bool operator<(const HuffmanNode &rhn) { return freq < rhn.freq; }
  bool operator>(const HuffmanNode &rhn) { return freq > rhn.freq; }
};

class HuffmanCode {
 public:
  explicit HuffmanCode(std::vector<std::pair<char, int>> chs);
  ~HuffmanCode();

  std::string get_code(char);

 private:
  void EnCode(std::vector<std::pair<char, int>> chs);
  void GenerateCode(const HuffmanNode &hn, std::string &str);
  bool is_leaf(const HuffmanNode &hn) { return hn.data != ' '; }

  std::vector<std::pair<char, std::string>> codes;
};

#endif
