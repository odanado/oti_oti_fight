/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_GAMESCENE_H_
#define INCLUDE_GAMESCENE_H_

#include <vector>
#include <string>
#include <tuple>
#include <random>

#include "SceneManager.h"
#include "Board.h"
#include "Player.h"
#include "NCursesUtil.h"

namespace oti_oti_fight {
class GameScene : public MyApp::Scene {
 public:
    void init() noexcept override;
    void update() noexcept override;
    void draw() noexcept override;

 private:
    std::vector<Player> players;
    Board board;
    std::mt19937 engine;
    static constexpr int OFFSET_X = 2;
    static constexpr int OFFSET_Y = 2;
    static constexpr int CELL_LENGTH = 3;

    void drawCell(NCursesUtil::Color color, int x, int y);
    void drawPlayer(NCursesUtil::Color color, int x, int y, Direction dir);
    void drawPlayerInfo(int idx);

    std::string getHumanAction(void);
    std::string getAIAction(void);
    std::tuple<int, int> getEnablePos();
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_GAMESCENE_H_
