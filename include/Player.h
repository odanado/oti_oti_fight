/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <string>
#include "Timer.h"
#include "Config.h"
#include "Direction.h"

namespace oti_oti_fight {
class Player {
 public:
    Player() = default;
    Player(const std::string &name, int x, int y, Direction dir,
           int remainingPlayers = Config::MAX_REMAINING_PLAYERS);
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setDirection(Direction dir) { this->dir = dir; }
    std::string getName(void) const { return name; }
    int getX(void) const { return x; }
    int getY(void) const { return y; }
    Direction getDirection(void) const { return dir; }
    int getRemainingPlayers(void) const { return remainingPlayers; }
    bool died(void) const {
        return Timer::now<millisec>() < nextRebornTime || remainingPlayers == 0;
    }

    void move(Direction dir);
    void attack();
    void fall() {
        --remainingPlayers;
        nextRebornTime = Timer::now<millisec>() + Config::TIME_UNTIL_REBORN;
    }

 private:
    using millisec = Timer::microseconds;
    void normalizePos(void);

    std::string name;
    int x, y;
    Direction dir;
    int remainingPlayers;
    millisec nextRebornTime;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_PLAYER_H_
