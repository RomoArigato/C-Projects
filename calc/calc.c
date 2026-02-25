
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt;

  while ((opt = getopt(argc, argv, "mh")) != -1) {
    switch (opt) {
    case 'm':
      // Use libm functions libm_unary_operators[]
      break;
    case 'h':
      printf(USAGE, argv[0]);
      return 0;
    case '?':
      fprintf(stderr, USAGE, argv[0]);
      return 1;
    }
  }

  char buffer[1024] = {0};
  printf("> ");
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    char *saveptr;
    bool error = false;
    const char *token = strtok_r(buffer, " ", &saveptr);

    while (token != NULL && !error) {
      double x;

      if (parse_double(token, &x)) {
        if (!stack_push(x)) {
          fprintf(stderr, ERROR_NO_SPACE, x);
          error = true;
        }
      }

      token = strtok_r(NULL, " ", &saveptr);
    }

    if (!error) {
      stack_print();
      printf("\n");
    }
    
    stack_clear();
    printf("> ");
  }

  return 0;
}
