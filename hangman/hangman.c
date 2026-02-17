/*
 * HANGMAN
 * ----------------------------------------------------------------------------
 * DESCRIPTION:
 * An implementation of hangman in C. At the start of the game, the following
 * are displayed:
 *
 * - Empty gallows
 * - A line for the secret phrase (with everything but the allowed special
 *   characters displayed as an underscore)
 * - A list for eliminated letters
 *
 *  The secret can be multiple words, include apostrophes, spaces, and
 *  hyphens, and be at most 256 characters long.
 *
 * RULES:
 * 1. If only special characters are present, the player automatically wins.
 * 2. The player will guess only one letter at a time.
 * 3. If the player guesses correctly, the letter is displayed in place of the
 *    corresponding underscore(s).
 * 4. If the player guesses wrong, the letter is displayed in the list of
 *    eleminated characters and the gallow is updated.
 * 5. If the player already guessed a letter, nothing happens.
 * 6. The game continues prompting guesses until the player wins or loses.
 * ----------------------------------------------------------------------------
 */

#include "hangman_helpers.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <secret phrase>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (!validate_secret(argv[1])) {
    return EXIT_FAILURE;
  }

  char *secret = argv[1];
  char phrase[MAX_LENGTH + 1] = {0};
  char eliminated[LOSING_MISTAKE + 1] = {0};

  // Mask the secret phrase
  strcpy(phrase, secret);

  for (int i = 0; phrase[i]; i++) {
    if (is_lowercase_letter(phrase[i])) {
      phrase[i] = '_';
    }
  }

  int mistakes = 0;

  do {
    display_game(phrase, eliminated, mistakes);

    printf("Guess a letter: ");
    char guess = read_letter();

    while (string_contains_character(phrase, guess) ||
           string_contains_character(eliminated, guess)) {
      printf("Guess a letter: ");
      guess = read_letter();
    }

    if (string_contains_character(secret, guess)) {
      for (int i = 0; secret[i] != '\0'; i++) {
        if (guess == secret[i]) {
          phrase[i] = secret[i];
        }
      }
      if (strcmp(phrase, secret) == 0) {
        break;
      }
    } else {
      eliminated[mistakes] = guess;
      mistakes++;
    }
  } while ((strcmp(phrase, secret) != 0) && mistakes < LOSING_MISTAKE);

  display_game(phrase, eliminated, mistakes);

  if (mistakes == LOSING_MISTAKE) {
    printf("You lose! The secret phrase was: %s\n", secret);
  } else {
    printf("You win! The secret phrase was: %s\n", secret);
  }

  return 0;
}
