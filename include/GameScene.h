/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_GAMESCENE_H_
#define INCLUDE_GAMESCENE_H_

#include <string>
#include <vector>
#include <memory>
#include <thread>

#include "SceneManager.h"
#include "Board.h"
#include "Player.h"
#include "NCursesUtil.h"
#include "Client.h"

namespace oti_oti_fight {
class GameScene : public MyApp::Scene {
 public:
    void init() noexcept override;
    void update() noexcept override;
    void draw() noexcept override;

    void start(const Timer::milliseconds &time, const std::vector<int> &xs,
               const std::vector<int> &ys);
    void move(int id, const std::string &act);
    void ok(int id);

 private:
    std::vector<Player> players;
    Board board;
    std::unique_ptr<Client> client;
    int id;
    static constexpr int OFFSET_X = 2;
    static constexpr int OFFSET_Y = 2;
    static constexpr int CELL_LENGTH = 2;

    void startServer();
    void startClient();
    std::thread serverThread;
    std::thread clientThread;
    void drawCell(NCursesUtil::Color color, int x, int y);
    void drawPlayer(NCursesUtil::Color color, int x, int y);
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_GAMESCENE_H_
