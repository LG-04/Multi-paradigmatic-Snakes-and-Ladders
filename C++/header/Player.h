//
// Created by liamg on 24/10/2025.
//

#ifndef C___PLAYER_H
#define C___PLAYER_H

#include <string>
using namespace std;

#include "Die.h"

class Player {
  protected:
    string name;
    int position;
    int suggestions;

  public:
    virtual ~Player() = default;
    Player(const string &name, int startingPosition, int startingSuggestions);

    virtual int handleMoveSuggestion(int initialRoll, Die *die) = 0;
    void move(int roll);

    string getName() { return name; }
    [[nodiscard]] int getPosition() const { return position; }
};


#endif //C___PLAYER_H
