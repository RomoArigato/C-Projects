
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt;
  int libm_flag = 0;

  while ((opt = getopt(argc, argv, "mh")) != -1) {
    switch (opt) {
    case '?':
      fprintf(stderr, USAGE, argv[0]);
      return 1;

    case 'h':
      printf(USAGE, argv[0]);
      return 0;

    case 'm':
      // Use libm functions
      libm_flag = 1;
      break;
    }
  }

  char buffer[1024] = {0};
  printf("> ");
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    // Get rid of the newline
    buffer[strcspn(buffer, "\n")] = 0;

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
      } else {
        switch (*token) {
        case '%':
          if (!apply_binary_operator(binary_operators['%'])) {
            fprintf(stderr, ERROR_BINARY_OPERATOR);
            error = true;
          }
          break;

        case '*':
          if (!apply_binary_operator(binary_operators['*'])) {
            fprintf(stderr, ERROR_BINARY_OPERATOR);
            error = true;
          }
          break;

        case '+':
          if (!apply_binary_operator(binary_operators['+'])) {
            fprintf(stderr, ERROR_BINARY_OPERATOR);
            error = true;
          }
          break;

        case '-':
          if (!apply_binary_operator(binary_operators['-'])) {
            fprintf(stderr, ERROR_BINARY_OPERATOR);
            error = true;
          }
          break;

        case '/':
          if (!apply_binary_operator(binary_operators['/'])) {
            fprintf(stderr, ERROR_BINARY_OPERATOR);
            error = true;
          }
          break;

        case 'a':
          if (libm_flag) {
            if (!apply_unary_operator(libm_unary_operators['a'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          } else {
            if (!apply_unary_operator(my_unary_operators['a'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          }
          break;

        case 'c':
          if (libm_flag) {
            if (!apply_unary_operator(libm_unary_operators['c'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          } else {
            if (!apply_unary_operator(my_unary_operators['c'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          }
          break;

        case 'r':
          if (libm_flag) {
            if (!apply_unary_operator(libm_unary_operators['r'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          } else {
            if (!apply_unary_operator(my_unary_operators['r'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          }
          break;

        case 's':
          if (libm_flag) {
            if (!apply_unary_operator(libm_unary_operators['s'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          } else {
            if (!apply_unary_operator(my_unary_operators['s'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          }
          break;

        case 't':
          if (libm_flag) {
            if (!apply_unary_operator(libm_unary_operators['t'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          } else {
            if (!apply_unary_operator(my_unary_operators['t'])) {
              fprintf(stderr, ERROR_UNARY_OPERATOR);
              error = true;
            }
          }
          break;

        default:
          if (strlen(token) > 1) {
            fprintf(stderr, ERROR_BAD_STRING, token);
          } else {
            fprintf(stderr, ERROR_BAD_CHAR, *token);
          }
          error = true;
          break;
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
