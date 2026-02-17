/*
 * PIG GAME
 * ----------------------------------------------------------------------------
 * DESCRIPTION:
 * This program simulates a simplified version of David Moffat's dice game
 * "Pass the Pigs", where players take turns "rolling a pig" until they reach a
 * target score of 100 points.
 *
 * RULES:
 * 1. Players take turns rolling the pig.
 * 2. Points are awarded based on how the pig lands (Razorback, Snouter, etc.).
 * 3. The player continues rolling and accumulating points until one of two
 *    things happens:
 *    a) The player rolls the 'SIDE' position (0 points), which ends their turn
 *    b) The player's total score reaches or exceeds 100 points, winning the
 *       game immediately
 * ----------------------------------------------------------------------------
 */

#include "names.h"

#include <stdio.h>
#include <stdlib.h>

#define WINNING_SCORE 100

typedef enum {
  SIDE = 0,
  RAZORBACK = 10,
  TROTTER = 10,
  SNOUTER = 15,
  JOWLER = 5
} Position;

const Position pig[7] = {
    SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER,
};

int main(void) {
  int num_players = 2;
  printf("Number of players (2 to 10)? ");
  int scanf_result = scanf("%d", &num_players);
  if (scanf_result < 1 || num_players < 2 || num_players > MAX_PLAYERS) {
    fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
    num_players = 2;
  }

  // Needed for reproducible results
  unsigned seed = 2023;
  printf("Random-number seed? ");
  scanf_result = scanf("%u", &seed);
  if (scanf_result < 1) {
    fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
  }

  // Initializes RNG for the first roll
  srandom(seed);

  int player_scores[MAX_PLAYERS];
  for (int i = 0; i < MAX_PLAYERS; i++) {
    player_scores[i] = 0;
  }

  // Start the game
  int index = 0;
  while (1) {
    printf("%s\n", player_name[index]);

    while (1) {
      int roll = random() % 7;
      int points = pig[roll];
      player_scores[index] += points;
      printf(" rolls %d, has %d\n", points, player_scores[index]);

      if (player_scores[index] >= WINNING_SCORE) {
        printf("%s won!\n", player_name[index]);
        return 0;
      }

      if (pig[roll] == SIDE) {
        break;
      }
    }

    index = (index + 1) % num_players;
  }
}
