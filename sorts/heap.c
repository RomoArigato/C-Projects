#include "gaps.h"
#include "stats.h"

#include <stdbool.h>

int max_child(int *A, int first, int last) {
  int left = 2 * first + 1;
  int right = 2 * first + 2;

  if (right <= last && A[right] > A[left]) {
    return right;
  }

  return left;
}

void fix_heap(int *A, int first, int last) {
  bool done = false;
  int parent = first;

  while (((2 * parent + 1) <= last) && !done) {
    int largest_child = max_child(A, parent, last);
    if (A[parent] < A[largest_child]) {
      int temp = A[parent];
      A[parent] = A[largest_child];
      A[largest_child] = temp;
      parent = largest_child;
    } else {
      done = true;
    }
  }
}

void build_heap(int *A, int first, int last) {
  if (last > 0) {
    for (int parent = (last - 1) / 2; parent > first - 1; parent--) {
      fix_heap(A, parent, last);
    }
  }
}

void heap_sort(Stats *stats, int *A, int n) {
  stats->moves = 0; // throwaway line so compiler stops crying
  int first = 0;
  int last = n - 1;
  build_heap(A, first, last);
  for (int leaf = last; leaf > first; leaf--) {
    int temp = A[first];
    A[first] = A[leaf];
    A[leaf] = temp;
    fix_heap(A, first, leaf - 1);
  }
}
