#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USAGE                                                                  \
  "SYNOPSIS\n"                                                                 \
  "   A collection of comparison-based sorting algorithms.\n\n"                \
  "USAGE\n"                                                                    \
  "   ./sorting_ref [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"        \
  "OPTIONS\n"                                                                  \
  "   -H              Display program help and usage.\n"                       \
  "   -a              Enable all sorts.\n"                                     \
  "   -h              Enable Heap Sort.\n"                                     \
  "   -b              Enable Batcher Sort.\n"                                  \
  "   -s              Enable Shell Sort.\n"                                    \
  "   -q              Enable Quick Sort.\n"                                    \
  "   -i              Enable Insertion Sort.\n"                                \
  "   -n length       Specify number of array elements (default: 100).\n"      \
  "   -p elements     Specify number of elements to print (default: 100).\n"   \
  "   -r seed         Specify random seed (default: 13371453).\n"

typedef void (*sort_fn)(Stats *stats, int *A, int n);

sort_fn sorting_functions[5] = {insertion_sort, heap_sort, shell_sort,
                                quick_sort, batcher_sort};

enum { INSERTION = 3, HEAP, SHELL, QUICK, BATCHER };

char *function_names[5] = {"Insertion Sort", "Heap Sort", "Shell Sort",
                           "Quick Sort", "Batcher Sort"};

int main(int argc, char *argv[]) {
  Set sorts = set_empty();
  Stats *stats = malloc(sizeof(Stats));
  stats->compares = stats->moves = 0;
  unsigned int seed = 13371453;
  int size = 100;
  int print_size = 100;
  int opt;

  while ((opt = getopt(argc, argv, "Hahbsqin:p:r:")) != -1) {
    switch (opt) {
    case 'a':
      sorts = set_universal();
      break;

    case 'r':
      sorts = set_insert(sorts, 0);
      seed = strtol(optarg, NULL, 10);
      break;

    case 'n':
      sorts = set_insert(sorts, 1);
      size = strtol(optarg, NULL, 10);
      break;

    case 'p':
      sorts = set_insert(sorts, 2);
      print_size = strtol(optarg, NULL, 10);
      break;

    case 'i':
      sorts = set_insert(sorts, 3);
      break;

    case 'h':
      sorts = set_insert(sorts, 4);
      break;

    case 's':
      sorts = set_insert(sorts, 5);
      break;

    case 'q':
      sorts = set_insert(sorts, 6);
      break;

    case 'b':
      sorts = set_insert(sorts, 7);
      break;

    case 'H':
      printf(USAGE);
      return 0;

    case '?':
      printf(USAGE);
      return 1;
    }
  }

  if (print_size > size) {
    print_size = size;
  }

  if ((opt == -1) && (sorts == set_empty())) {
    printf("Select at least one sort to perform.\n");
    printf(USAGE);
    return 1;
  }

  srandom(seed);
  int *arr = malloc(size * sizeof(int));
  int *arr_copy = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    arr[i] = random() & 0x3FFFFFFF;
  }

  for (int i = INSERTION; i <= BATCHER; i++) {
    if (set_member(sorts, i)) {
      // i starts at 3
      sort_fn sort = sorting_functions[i - 3];
      char *name = function_names[i - 3];
      memcpy(arr_copy, arr, size * sizeof(int));
      sort(stats, arr_copy, size);
      print_stats(stats, name, size);

      if (print_size) {
        for (int i = 0; i < print_size; i++) {
          if (i > 0 && i % 5 == 0) {
            printf("\n");
          }
          printf("%13d", arr_copy[i]);
        }
        printf("\n");
      }
      reset(stats);
    }
  }

  free(arr);
  free(arr_copy);
  free(stats);
  return 0;
}
