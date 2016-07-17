/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <algorithm>
#include <string>
#include <chrono>
#include "Config.h"
#include "Player.h"

namespace oti_oti_fight {

Player::Player(const std::string &name, int x, int y, Direction dir,
               int remainingPlayers)
    : name(name),
      x(x),
      y(y),
      dir(dir),
      remainingPlayers(remainingPlayers),
      nextRebornTime(Timer::now<millisec>()) {}

void Player::move(Direction act) {
    switch (act) {
        case Direction::UP:
            --y;
            break;

        case Direction::DOWN:
            ++y;
            break;

        case Direction::LEFT:
            --x;
            break;

        case Direction::RIGHT:
            ++x;
            break;
    }
    dir = act;
    normalizePos();
}

void Player::normalizePos(void) {
    x = std::max(0, x);
    x = std::min(x, Config::BOARD_WIDTH - 1);
    y = std::max(0, y);
    y = std::min(y, Config::BOARD_HEIGHT - 1);
}
}  // namespace oti_oti_fight
