#include "insert.h"

void insertion_sort(Stats *stats, int *arr, int length) {
  stats->moves = 0; // throway line so compiler stops bitching
  for (int k = 1; k < length; k++) {
    int j = k;
    int temp = arr[k];
    while (j >= 1 && temp < arr[j - 1]) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = temp;
  }
}
