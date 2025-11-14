//
// Created by liamg on 24/10/2025.
//

#ifndef C___GAME_H
#define C___GAME_H
#include <memory>
#include <vector>

#include "Die.h"
#include "Player.h"

class Game {
  private:
    const int BOARD_SIZE = 35;

    int turn = 0;
    bool playing = false;

    vector<unique_ptr<Player> > players;
    unique_ptr<Die> die;

    void setup();
    void play();

  public:
    Game(vector<unique_ptr<Player> > players_ptr, unique_ptr<Die> die_ptr);

    void start();
};

#endif //C___GAME_H
