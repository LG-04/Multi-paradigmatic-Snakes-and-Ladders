//
// Created by liamg on 24/10/2025.
//

#include "../header/HumanPlayer.h"

#include <iostream>

#include <unistd.h>

#include "../header/GameBoard.h"

HumanPlayer::HumanPlayer(const string &name, const int position, const int suggestions) : Player(name, position, suggestions) {
}

int HumanPlayer::handleMoveSuggestion(const int initialRoll, Die* die) {
  int finalRoll = initialRoll;

  if (suggestions > 0) {
    cout << "You have " << suggestions
              << " remaining suggestions, do you want to use one? (y/n): ";

    char useSuggestion;
    cin >> useSuggestion;

    while (cin.get() != '\n') {}

    if (useSuggestion == 'y') {
      suggestions--;

      if (int newPos = position + initialRoll; GameBoard::isInSnakes(newPos)) {
        cout << "You would have hit a snake, rolling again..." << endl;

        while (GameBoard::isInSnakes(newPos)) {
          finalRoll = die->roll();
          newPos = position + finalRoll;
        }
      }
      else if (GameBoard::isInLadders(newPos)) {
        cout << "You will hit a ladder, moving player..." << endl;
      }
      else {
        cout << "Safe to move, moving player..." << endl;
      }
    }

    usleep(500000);
  }

  return finalRoll;
}