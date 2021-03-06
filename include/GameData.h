/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_GAMEDATA_H_
#define INCLUDE_GAMEDATA_H_

#include <vector>
#include <string>

#include "Board.h"
#include "Input.h"

namespace oti_oti_fight {
struct GameData {
    Board board;
    Input input;
    std::vector<std::string> rank;
    std::vector<std::string> log;
    bool isSoroPlay = true;
    bool isFinish;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_GAMEDATA_H_
