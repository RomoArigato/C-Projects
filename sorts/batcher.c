#include "batcher.h"
#include "stats.h"

#include <stdio.h>

void comparator(int *A, int x, int y) {
  if (A[x] > A[y]) {
    int temp = A[x];
    A[x] = A[y];
    A[y] = temp;
  }
}

void batcher_sort(Stats *stats, int *A, int n) {
  stats->moves = 0; // throwaway line so compiler stops crying
  if (n == 0) {
    return;
  }

  int len = n;
  int t = 0;

  while (len > 0) {
    t++;
    len >>= 1;
  }

  int p = 1 << (t - 1);

  while (p > 0) {
    int q = 1 << (t - 1);
    int r = 0;
    int d = p;

    while (d > 0) {
      for (int i = 0; i < n - d; i++) {
        if ((i & p) == r) {
          comparator(A, i, i + d);
        }
      }
      d = q - p;
      q >>= 1;
      r = p;
    }

    p >>= 1;
  }
}
