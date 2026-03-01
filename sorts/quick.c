#include "gaps.h"
#include "stats.h"

int partition(int *A, int lo, int hi) {
  int i = lo - 1;

  for (int j = lo; j < hi; j++) {
    if (A[j] < A[hi]) {
      i++;
      int temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }

  i++;
  int temp = A[i];
  A[i] = A[hi];
  A[hi] = temp;
  return i;
}

void quick_sorter(int *A, int lo, int hi) {
  if (lo < hi) {
    int p = partition(A, lo, hi);
    quick_sorter(A, lo, p - 1);
    quick_sorter(A, p + 1, hi);
  }
}

void quick_sort(Stats *stats, int *A, int n) {
  stats->moves = 0; // throwaway line so compiler stops crying
  quick_sorter(A, 0, n - 1);
}
