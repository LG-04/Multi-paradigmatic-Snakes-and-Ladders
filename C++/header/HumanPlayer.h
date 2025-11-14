//
// Created by liamg on 24/10/2025.
//

#ifndef C___HUMANPLAYER_H
#define C___HUMANPLAYER_H
#include "Player.h"

class HumanPlayer final: public Player {
  public:
    HumanPlayer(const string &name, int position, int suggestions);

    int handleMoveSuggestion(int initialRoll, Die *die) override;
};


#endif //C___HUMANPLAYER_H
