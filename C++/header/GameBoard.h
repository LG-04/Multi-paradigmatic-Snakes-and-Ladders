//
// Created by liamg on 24/10/2025.
//

#ifndef C___GAMEBOARD_H
#define C___GAMEBOARD_H

class GameBoard {
  public:
    static bool isInSnakes(int position);
    static bool isInLadders(int position);
    static int getSnakeEnd(int startPos);
    static int getLadderEnd(int startPos);
};


#endif //C___GAMEBOARD_H
