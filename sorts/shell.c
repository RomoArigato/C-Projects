#include "gaps.h"
#include "stats.h"

void shell_sort(Stats *stats, int *A, int n) {
  for (int i = 0; i < GAPS; i++) {
    for (int k = gaps[i]; k < n; k++) {
      int j = k;
      int temp;
      move(stats, temp = A[k]);

      while (j >= gaps[i] && (cmp(stats, temp, A[j - gaps[i]]) == -1)) {
        move(stats, A[j] = A[j - gaps[i]]);
        j -= gaps[i];
      }

      move(stats, A[j] = temp);
    }
  }
}
