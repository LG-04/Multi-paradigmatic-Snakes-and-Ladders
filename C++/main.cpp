#include <iostream>

#include "header/ComputerPlayer.h"
#include "header/Game.h"
#include "header/HumanPlayer.h"

int main() {
  srand(time(nullptr));

  cout << "Liam Grey - 22467895\n\n" << endl;

  auto players = vector<unique_ptr<Player>>();
  players.push_back(make_unique<HumanPlayer>("p1", 1, 3));
  players.push_back(make_unique<ComputerPlayer>("p2", 1, 0));

  Game game(move(players), make_unique<Die>());
  game.start();

  return 0;
}
