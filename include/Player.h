/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <string>
#include "Config.h"
#include "Direction.h"

namespace oti_oti_fight {
class Player {
 public:
    Player() = default;
    Player(const std::string &name, int x, int y, Direction dir,
           int remainingPlayers = Config::MAX_REMAINING_PLAYERS);
    std::string getName(void) const { return name; }
    int getX(void) const { return x; }
    int getY(void) const { return y; }
    Direction getDirection(void) const { return dir; }
    int getRemainingPlayers(void) { return remainingPlayers; }
    bool died(void) const { return remainingPlayers == 0; }

    void move(Direction);
    void attack();

 private:
    void normalizePos(void);
    std::string name;
    int x, y;
    Direction dir;
    int remainingPlayers;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_PLAYER_H_
