//
// Created by liamg on 24/10/2025.
//

#include "../header/Player.h"

#include <iostream>
#include <ostream>

#include "../header/GameBoard.h"

Player::Player(const string &name, const int startingPosition, const int startingSuggestions) {
  this->name = name;
  this->position = startingPosition;
  this->suggestions = startingSuggestions;
}

void Player::move(const int roll) {
  cout << name << " moves " << roll << " spaces" << endl;

  const int newPos = position + roll;
  int finalPos = newPos;

  if (GameBoard::isInLadders(newPos)) {
    finalPos = GameBoard::getLadderEnd(newPos);
    const int diff = finalPos - newPos;
    cout << "Hit a ladder! - moved " << diff << " spaces forwards" << endl;
  } else if (GameBoard::isInSnakes(newPos)) {
    finalPos = GameBoard::getSnakeEnd(newPos);
    const int diff = newPos - finalPos;
    cout << "Hit a snake! - moved " << diff << " spaces backwards" << endl;
  }

  this->position = finalPos;
}
