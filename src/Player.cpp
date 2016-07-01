/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <algorithm>
#include "Config.h"
#include "Player.h"

namespace oti_oti_fight {

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
    x = std::min(x, Config::BOARD_WIDTH);
    y = std::max(0, y);
    y = std::min(y, Config::BOARD_HEIGHT);
}
}  // namespace oti_oti_fight
