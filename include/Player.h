/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <string>
#include "Config.h"

namespace oti_oti_fight {
class Player {
 public:
    enum struct Move { UP, DOWN, LEFT, RIGHT, ATTACK, NONE };

    Player() = default;
    Player(const std::string &name, int x, int y,
           int remainingPlayers = Config::MAX_REMAINING_PLAYERS);
    std::string getName(void) const { return name; }
    int getX(void) const { return x; }
    int getY(void) const { return y; }
    int getRemainingPlayers(void) { return remainingPlayers; }
    bool died(void) const { return remainingPlayers == 0; }

    void move(Move);

 private:
    void normalizePos(void);
    std::string name;
    int x, y;
    int remainingPlayers;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_PLAYER_H_
