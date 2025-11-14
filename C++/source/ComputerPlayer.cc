//
// Created by liamg on 24/10/2025.
//

#include "../header/ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(const string &name, const int position, const int suggestions) : Player(name, position, suggestions) {
}

int ComputerPlayer::handleMoveSuggestion(const int initialRoll, Die* die) {
  return initialRoll;
}
