/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */
#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include "Timer.h"

namespace oti_oti_fight {
namespace Config {
constexpr int MAX_REMAINING_PLAYERS = 5;

constexpr int SQUARE_WIDTH = 2;
constexpr int SQUARE_HEIGHT = 2;

constexpr int BLOCK_WIDTH = 8;
constexpr int BLOCK_HEIGHT = 8;

constexpr int BOARD_WIDTH = SQUARE_WIDTH * BLOCK_WIDTH;
constexpr int BOARD_HEIGHT = SQUARE_HEIGHT * BLOCK_HEIGHT;

constexpr int FALL_UNTIL_TIME = 3000;
constexpr int FALL_INCRESE_TIME = 500;
constexpr int ENABLE_UNTIL_TIME = 5000;

constexpr int PLAYERS = 4;

// 復活するまでの時間
constexpr auto TIME_UNTIL_REBORN = Timer::milliseconds(3000);
}  // namespace Config
}  // namespace oti_oti_fight
#endif  // INCLUDE_CONFIG_H_
