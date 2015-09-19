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

int **NewTwoDimArray(int x, int y);

#endif
