#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

template <typename T>
void swap(T &x, T &y) {
  T tmp = x;
  x = y;
  y = tmp;
}

template <typename T>
void PrintArray(T arr[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
T **NewTwoDimArray(int x, int y) {
  T **arr = new T *[x];

  for (int i = 0; i < x; ++i) {
    arr[i] = new T[y];
  }

  return arr;
}

template <typename T>
T **NewTwoDimArray(int x, int y, T init) {
  T **arr = new T *[x];

  for (int i = 0; i < x; ++i) {
    arr[i] = new T[y];

    for (int j = 0; j < y; ++j) {
      arr[i][j] = init;
    }
  }

  return arr;
}

#endif
