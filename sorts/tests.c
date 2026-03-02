#include "set.h"

#include <assert.h>
#include <stdio.h>

void test_set(void) {
  assert(set_empty() == 0);
  assert(set_universal() == 255);
  assert(set_member(0xF, 3));
  assert(set_insert(0xF, 4) == 31);
  assert(set_remove(0xF, 3) == 7);
  assert(set_union(0xC, 3) == 15);
  assert(set_intersect(0xD, 9) == 9);
  assert(set_difference(0xA, 0xD) == 2);
  assert(set_complement(set_empty()) == set_universal());
  assert(set_complement(set_universal()) == set_empty());
  assert(set_complement(1) == 254);
}

int main(void) {
  test_set();
  printf("Passed all tests!\n");
}
