/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <algorithm>
#include <string>
#include "Config.h"
#include "Player.h"

namespace oti_oti_fight {

Player::Player(const std::string &name, int x, int y, int remainingPlayers)
    : name(name), x(x), y(y), remainingPlayers(remainingPlayers) {}

void Player::move(Player::Move act) {
    switch (act) {
        case Move::UP:
            --y;
            break;

        case Move::DOWN:
            ++y;
            break;

        case Move::LEFT:
            --x;
            break;

        case Move::RIGHT:
            ++x;
            break;

        case Move::ATTACK:
            // TODO(odanado): ato de zisso suru
            break;

        case Move::NONE:
            break;
    }
    normalizePos();
}

void Player::normalizePos(void) {
    x = std::max(0, x);
    x = std::min(x, Config::BOARD_WIDTH - 1);
    y = std::max(0, y);
    y = std::min(y, Config::BOARD_HEIGHT - 1);
}
}  // namespace oti_oti_fight
