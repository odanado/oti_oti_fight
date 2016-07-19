/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <boost/asio.hpp>

#include "GameScene.h"
#include "NCursesUtil.h"
#include "Config.h"
#include "Server.h"

namespace oti_oti_fight {
void GameScene::init() noexcept {
    using NCursesUtil::clear;
    clear();
    serverThread = std::thread([&]() { startServer(); });
    std::this_thread::sleep_for(Timer::milliseconds(500));
    clientThread = std::thread([&]() { startClient(); });
    std::this_thread::sleep_for(Timer::milliseconds(500));
    client->join();
}

void GameScene::startServer() {
    boost::asio::io_service ioService;
    auto server = Server(&ioService, 50000);
    ioService.run();
}

void GameScene::startClient() {
    boost::asio::io_service ioService;
    client = std::make_unique<Client>(&ioService);
    ioService.run();
}

void GameScene::update() noexcept {
    for (auto &player : players) {
        int x = player.getX();
        int y = player.getY();
        if (!board.valid(x, y)) {
            player.fall();
        }
    }
    if (data->input.keyUp.pressed) {
        client->move(id, "up");
    }
    if (data->input.keyDown.pressed) {
        client->move(id, "down");
    }
    if (data->input.keyLeft.pressed) {
        client->move(id, "left");
    }
    if (data->input.keyRight.pressed) {
        client->move(id, "right");
    }
    if (data->input.keyX.pressed) {
        client->move(id, "attack");
    }

    board.update();
}

void GameScene::draw() noexcept {
    using NCursesUtil::refresh;
    using NCursesUtil::Color;

    for (int x = 0; x < Config::BOARD_WIDTH; x++) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            int v = x + y * Config::BOARD_HEIGHT;
            int nx = (v & 0xf) >> 1;
            int ny = v >> 5;

            auto state = board.getState(x, y);
            switch (state) {
                case Board::State::ENABLE:
                    if ((nx + ny) % 2 == 0)
                        drawCell(Color::GREEN, x, y);
                    else
                        drawCell(Color::BLUE, x, y);

                    break;
                case Board::State::UNSTABLE:
                    drawCell(Color::SUB_BLACK, x, y);
                    break;
                case Board::State::DISABLE:
                    drawCell(Color::BLACK, x, y);
                    break;
            }
        }
    }
    for (const auto &player : players) {
        if (player.died()) {
            drawPlayer(Color::YELLOW, player.getX(), player.getY());
        } else {
            drawPlayer(Color::RED, player.getX(), player.getY());
        }
    }
    refresh();
}

void GameScene::start(const Timer::milliseconds &time,
                      const std::vector<int> &xs, const std::vector<int> &ys) {
    NCursesUtil::debug(std::to_string(xs.size()));
    players = std::vector<Player>(xs.size());
    for (int i = 0; i < players.size(); i++) {
        players.emplace_back("test", xs[i], ys[i], Direction::RIGHT);
    }
}
void GameScene::move(int id, const std::string &act) {
    if (act == "attack") {
        board.attack(0, players[id].getX(), players[id].getY(),
                     players[id].getDirection());
    } else {
        Direction dir;
        if (act == "up") dir = Direction::UP;
        if (act == "down") dir = Direction::DOWN;
        if (act == "right") dir = Direction::RIGHT;
        if (act == "left") dir = Direction::LEFT;
        players[id].move(dir);
    }
}

void GameScene::ok(int id) {
    std::cerr << __LINE__ << std::endl;
    this->id = id;
}

void GameScene::drawCell(NCursesUtil::Color color, int x, int y) {
    using NCursesUtil::drawDot;
    assert(0 <= x && x < Config::BOARD_WIDTH);
    assert(0 <= y && y < Config::BOARD_HEIGHT);
    for (int dx = 0; dx < CELL_LENGTH; dx++) {
        for (int dy = 0; dy < CELL_LENGTH; dy++) {
            int nx = CELL_LENGTH * x + OFFSET_X + dx;
            int ny = CELL_LENGTH * y + OFFSET_Y + dy;
            drawDot(color, nx, ny);
        }
    }
}

void GameScene::drawPlayer(NCursesUtil::Color color, int x, int y) {
    using NCursesUtil::drawDot;
    assert(0 <= x && x < Config::BOARD_WIDTH);
    assert(0 <= y && y < Config::BOARD_HEIGHT);
    for (int dx = 0; dx < CELL_LENGTH; dx++) {
        for (int dy = 0; dy < CELL_LENGTH; dy++) {
            int nx = CELL_LENGTH * x + OFFSET_X + dx;
            int ny = CELL_LENGTH * y + OFFSET_Y + dy;
            drawDot(color, nx, ny);
        }
    }
}
}  // namespace oti_oti_fight
