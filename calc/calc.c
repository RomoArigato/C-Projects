
#include "messages.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt = getopt(argc, argv, "hm");
  
  switch (opt) {
  case 'm':
    // Use libm functions libm_unary_operators[]
    break;
  case 'h':
    printf(USAGE, argv[0]);
    break;
  default:
    fprintf(stderr, USAGE, argv[0]);
    return 1;
  }


  return 0;
}
