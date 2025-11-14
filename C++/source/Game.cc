//
// Created by liamg on 24/10/2025.
//

#include "../header/Game.h"

#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <unistd.h>

#include "../header/HumanPlayer.h"

Game::Game(vector<unique_ptr<Player> > players_ptr, unique_ptr<Die> die_ptr)
  : players(move(players_ptr)), die(move(die_ptr)) {
}

void Game::start() {
  setup();
  play();
}

void Game::setup() {
  turn = rand() % 2;
  playing = true;
}

void Game::play() {
  while (playing) {
    Player *currentPlayer = players[turn].get();

    if (turn == 0) {
      // p1
      cout << "-- Your turn --" << endl;
      cout << "Press enter to roll the die...";
      cin.get();
    } else {
      // p2
      cout << "-- Opponents turn --" << endl;
    }

    usleep(500000);
    const int initialRoll = die->roll();
    cout << currentPlayer->getName() << " rolled a " << initialRoll << endl;
    usleep(300000);

    const int finalRoll = currentPlayer->handleMoveSuggestion(initialRoll, die.get());
    currentPlayer->move(finalRoll);

    if (currentPlayer->getPosition() >= BOARD_SIZE) {
      cout << "Game over, " << currentPlayer->getName() << " wins" << endl;
      playing = false;
    } else {
      turn = 1 - turn;
      cout << endl;
    }
  }
}
