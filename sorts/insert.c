#include "insert.h"
#include "stats.h"

void insertion_sort(Stats *stats, int *arr, int length) {
  for (int k = 1; k < length; k++) {
    int j = k;
    int temp;
    move(stats, temp = arr[k]);
    while (j >= 1 && (cmp(stats, temp, arr[j - 1]) == -1)) {
      move(stats, arr[j] = arr[j - 1]);
      j--;
    }
    move(stats, arr[j] = temp);
  }
}
