#include "gaps.h"
#include "stats.h"

#include <stdio.h>

void shell_sort(Stats *stats, int *A, int n) {
  stats->moves = 0; // throwaway line so compiler stops bitching
  for (int i = 0; i < GAPS; i++) {
    for (int k = gaps[i]; k < n; k++) {
      int j = k;
      int temp = A[k];
      while (j >= gaps[i] && temp < A[j - gaps[i]]) {
        A[j] = A[j - gaps[i]];
        j -= gaps[i];
      }
      A[j] = temp;
    }
  }
}
