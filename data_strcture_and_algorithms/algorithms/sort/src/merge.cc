#include "merge.h"

void m_sort(int arr[], int l, int r);
void m_merge(int arr[], int l, int m, int r);

void merge_sort(int arr[], int n) { m_sort(arr, 0, n - 1); }

void m_sort(int arr[], int l, int r) {
  if (l < r) {
    int mid = (l + r) / 2;
    // int mid = l + (r - l) / 2;
    m_sort(arr, l, mid);
    m_sort(arr, mid + 1, r);
    m_merge(arr, l, mid + 1, r);
  }
}

// sorted parts are: [l, m - 1], [m, r]
// carefully handle the index of arr and rarr!!!
void m_merge(int arr[], int l, int m, int r) {
  int n1 = m - l;
  int n2 = r - m + 1;

  int *rarr = new int[n2];
  for (int i = 0; i < n2; ++i) {
    rarr[i] = arr[m + i];
  }

  while (n1 > 0 && n2 > 0) {
    if (arr[l + n1 - 1] > rarr[n2 - 1]) {
      arr[l + n1 + n2 - 1] = arr[l + n1 - 1];
      --n1;
    } else {
      arr[l + n1 + n2 - 1] = rarr[n2 - 1];
      --n2;
    }
  }

  while (n2 > 0) {
    arr[l + n1 + n2 - 1] = rarr[n2 - 1];
    --n2;
  }

  delete[] rarr;
}
