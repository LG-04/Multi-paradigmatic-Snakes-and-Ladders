#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int BOARD_SIZE = 35;

struct BoardFeature {
  int start;
  int end;
};

const struct BoardFeature LADDERS[] = {
  {.start = 2, .end = 9},
  {.start = 11, .end = 28},
  {.start = 19, .end = 31}
};

const int NUM_LADDERS = sizeof(LADDERS) / sizeof(LADDERS[0]);

const struct BoardFeature SNAKES[] = {
  {.start = 12, .end = 4},
  {.start = 27, .end = 12},
  {.start = 30, .end = 20}
};

const int NUM_SNAKES = sizeof(SNAKES) / sizeof(SNAKES[0]);

#define MAX_NAME_LENGTH 3

struct Player {
  char name[MAX_NAME_LENGTH];
  int position;
};

int rollDie() {
  return rand() % 6 + 1;
}

int isInSnakes(const int position) {
  for (int i = 0; i < NUM_SNAKES; i++) {
    if (SNAKES[i].start == position) return 1;
  }
  return 0;
}

int isInLadders(const int position) {
  for (int i = 0; i < NUM_LADDERS; i++) {
    if (LADDERS[i].start == position) return 1;
  }
  return 0;
}

int getLadderEnd(const int start) {
  for (int i = 0; i < NUM_LADDERS; i++) {
    if (LADDERS[i].start == start) return LADDERS[i].end;
  }
  return start;
}

int getSnakeEnd(const int start) {
  for (int i = 0; i < NUM_SNAKES; i++) {
    if (SNAKES[i].start == start) return SNAKES[i].end;
  }
  return start;
}

void setupGame(struct Player players[], int *suggestions_ptr, int *turn_ptr) {
  printf("Liam Grey - 22467895\n\n");

  printf("Game is starting...\n");
  usleep(500000);

  strcpy(players[0].name, "p1");
  players[0].position = 1;

  strcpy(players[1].name, "p2");
  players[1].position = 1;

  *suggestions_ptr = 3;
  *turn_ptr = rand() % 2;

  printf("%s will move first\n\n", players[*turn_ptr].name);
}

int handleMoveSuggestion(const int currentPlayerPos,
                         const int roll,
                         int *suggestions_ptr,
                         const int turn) {
  int finalRoll = roll;

  if (turn == 0 && *suggestions_ptr > 0) {
    printf("You have %d remaining suggestions, do you want to use one? (y/n): ", *suggestions_ptr);
    const int useSuggestion = getchar();
    int c;
    //while ((c = getchar()) != '\n' && c != EOF) {}

    if (useSuggestion == 'y') {
      *suggestions_ptr -= 1;

      int newPos = currentPlayerPos + roll;

      if (isInSnakes(newPos)) {
        printf("You would have hit a snake, rolling again...\n");
        usleep(500000);
        while (isInSnakes(newPos)) {
          finalRoll = rollDie();
          newPos = currentPlayerPos + finalRoll;
        }
      } else if (isInLadders(newPos)) {
        printf("You will hit a ladder, moving player...\n");
        usleep(500000);
      } else {
        printf("Safe to move, moving player...\n");
      }
    }
  }

  return finalRoll;
}

int movePlayer(struct Player players[], const int roll, const int turn) {
  printf("%s moves %d spaces\n", players[turn].name, roll);

  const int newPos = players[turn].position + roll;
  int finalPos = newPos;

  if (isInLadders(newPos)) {
    finalPos = getLadderEnd(newPos);
    const int diff = finalPos - newPos;
    printf("Hit a ladder! - moved %d spaces forwards\n", diff);
  } else if (isInSnakes(newPos)) {
    finalPos = getSnakeEnd(newPos);
    const int diff = newPos - finalPos;
    printf("Hit a snake! - moved %d spaces backwards\n", diff);
  }

  return finalPos;
}

int main() {
  srand(time(NULL)); // random seed

  struct Player players[2];
  int suggestions, turn;
  setupGame(players, &suggestions, &turn);

  int playing = 1;
  while (playing) {
    const int currentPlayerPos = players[turn].position;

    if (turn == 0) {
      // p1
      printf("-- Your turn --\n");
      printf("Press enter to roll the die...");
      getchar();
    } else {
      // p2
      printf("-- Opponents turn --\n");
    }

    usleep(500000);
    const int initialRoll = rollDie();
    printf("%s rolled a %d\n", players[turn].name, initialRoll);
    usleep(300000);

    const int finalRoll = handleMoveSuggestion(currentPlayerPos, initialRoll, &suggestions, turn);
    players[turn].position = movePlayer(players, finalRoll, turn);

    if (players[turn].position >= BOARD_SIZE) {
      printf("Game over, %s wins\n", players[turn].name);
      playing = 0;
    } else {
      turn = 1 - turn;
      printf("\n");
    }
  }

  return 0;
}
