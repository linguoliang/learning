#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

void swap(int *a, int *b);

template <typename T>
void print_array(T arr[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int **new_two_dim_array(int x, int y);

#endif
