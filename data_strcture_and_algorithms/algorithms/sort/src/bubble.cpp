#include "bubble.h"

void bubble_sort(int arr[], int n) {
  for (int i = 0; i < n - 1; ++i) {
    bool swaped = false;
    for (int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        swaped = true;
      }
    }
    if (swaped == false) {
      break;
    }
  }
}

// void bubble_sort(int arr[], int n) {
//   for (int i = 0; i < n - 1; ++i) {
//     for (int j = 0; j < n - 1 - i; j++) {
//       if (arr[j] > arr[j + 1]) {
//         swap(&arr[j], &arr[j + 1]);
//       }
//     }
//   }
// }
