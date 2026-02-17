#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_lowercase_letter(char c) { return (c >= 'a' && c <= 'z'); }

bool validate_secret(const char *secret) {
  if (strlen(secret) > MAX_LENGTH) {
    fprintf(stderr, "the secret phrase is over 256 characters.\n");
    return false;
  }

  char c;
  while ((c = *secret++)) {
    if (!is_lowercase_letter(c) && !string_contains_character(punctuation, c)) {
      fprintf(stderr, "invalid character: %c\n", c);
      return false;
    }
  }

  return true;
}

bool string_contains_character(const char *s, char c) {
  return strchr(s, c) != NULL;
}

char read_letter(void) {
  char c;
  scanf(" %c", &c);
  return c;
}

void display_game(char *phrase, char *eliminated, int mistakes) {
  printf(CLEAR_SCREEN);
  printf("%s\n", arts[mistakes]);
  printf("    Phrase: %s\n", phrase);
  printf("Eliminated: ");
  for (char c = 'a'; c != 'z'; c++) {
    if (string_contains_character(eliminated, c)) {
      printf("%c", c);
    }
  }
  printf("\n\n");
}
