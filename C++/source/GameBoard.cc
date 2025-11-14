//
// Created by liamg on 24/10/2025.
//

#include "../header/GameBoard.h"

#include <algorithm>

using namespace std;

struct BoardFeature {
  int start;
  int end;
};

constexpr BoardFeature LADDERS[] = {
  {.start = 2, .end = 9},
  {.start = 11, .end = 28},
  {.start = 19, .end = 31}
};

constexpr BoardFeature SNAKES[] = {
  {.start = 12, .end = 4},
  {.start = 27, .end = 12},
  {.start = 30, .end = 20}
};

bool GameBoard::isInSnakes(const int position) {
  return ranges::any_of(SNAKES, [&](const BoardFeature& feature) {
    return feature.start == position;
  });
}

int GameBoard::getSnakeEnd(const int startPos) {
  for (auto [start, end] : SNAKES) if (start == startPos) return end;

  return startPos;
}

bool GameBoard::isInLadders(const int position) {
  return ranges::any_of(LADDERS, [&](const BoardFeature& feature) {
    return feature.start == position;
  });
}

int GameBoard::getLadderEnd(const int startPos) {
  for (auto [start, end] : LADDERS) {
    if (start == startPos) return end;
  }

  return startPos;
}