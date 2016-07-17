/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_GAMESCENE_H_
#define INCLUDE_GAMESCENE_H_

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
    Player player;
    Board board;
    static constexpr int OFFSET_X = 2;
    static constexpr int OFFSET_Y = 2;
    static constexpr int CELL_LENGTH = 2;

    void drawCell(NCursesUtil::Color color, int x, int y);
    void drawPlayer(NCursesUtil::Color color, int x, int y);
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_GAMESCENE_H_
