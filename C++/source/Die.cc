//
// Created by liamg on 24/10/2025.
//

#include "../header/Die.h"

#include <cstdlib>

Die::Die() = default;

int Die::roll() {
  return rand() % 6 + 1;
}
