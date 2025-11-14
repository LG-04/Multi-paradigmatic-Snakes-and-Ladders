//
// Created by liamg on 24/10/2025.
//

#ifndef C___COMPUTERPLAYER_H
#define C___COMPUTERPLAYER_H
#include "Player.h"

class ComputerPlayer final: public Player {
  public:
    ComputerPlayer(const string &name, int position, int suggestions);

    int handleMoveSuggestion(int initialRoll, Die *die) override;
};


#endif //C___COMPUTERPLAYER_H
