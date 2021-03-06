/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <algorithm>

#include "GameScene.h"
#include "NCursesUtil.h"
#include "Config.h"

namespace oti_oti_fight {
void GameScene::init() noexcept {
    using NCursesUtil::clear;
    clear();
    data->rank.clear();
    data->log.resize(Config::PLAYERS);
    players.resize(Config::PLAYERS);
    for (int i = 0; i < Config::PLAYERS; i++) {
        int x, y;
        std::tie(x, y) = getEnablePos();
        std::uniform_int_distribution<> dist(0, 3);
        auto dir = static_cast<Direction>(dist(engine));
        players[i] = Player("player" + std::to_string(i), x, y, dir);
    }
}

void GameScene::update() noexcept {
    if (isFinish()) {
        for (const auto &player : players) {
            if (player.getRemainingPlayers() != 0) {
                std::string str = std::to_string(1) + ": " + player.getName();
                data->rank.emplace_back(str);
            }
        }
        changeScene("Result");
    }
    for (int i = 0; i < players.size(); i++) {
        auto &player = players[i];
        if (player.died()) continue;
        int x = player.getX();
        int y = player.getY();
        if (!board.valid(x, y)) {
            player.fall();
            if (player.getRemainingPlayers() == 0) {
                int r = players.size() - data->rank.size();
                std::string str = std::to_string(r) + ": " + player.getName();
                data->rank.emplace_back(str);
            } else {
                std::tie(x, y) = getEnablePos();
                player.setX(x);
                player.setY(y);
            }
            continue;
        }
        std::string act;
        if (i == 0) {
            act = getHumanAction();
        } else {
            act = getAIAction();
        }
        if (act == "attack") {
            board.attack(i, player.getX(), player.getY(),
                         player.getDirection());
            data->log[i] += "A";
            continue;
        }
        if (act == "none") {
            data->log[i] += "N";
            continue;
        }
        auto valid = [&](int x, int y) {
            return board.valid(x, y) &&
                   board.getState(x, y) != Board::State::DISABLE;
        };
        Direction dir;
        int dx = 0, dy = 0;
        if (act == "up") {
            dy = -1;
            dir = Direction::UP;
            data->log[i] += "U";
        }
        if (act == "down") {
            dy = 1;
            dir = Direction::DOWN;
            data->log[i] += "D";
        }
        if (act == "left") {
            dx = -1;
            dir = Direction::LEFT;
            data->log[i] += "L";
        }
        if (act == "right") {
            dx = 1;
            dir = Direction::RIGHT;
            data->log[i] += "R";
        }

        player.setDirection(dir);
        if (valid(x + dx, y + dy)) {
            player.move(dir);
        }
    }
    board.update();
}

std::string GameScene::getHumanAction() {
    if (data->input.keyUp.pressed) {
        return "up";
    }
    if (data->input.keyDown.pressed) {
        return "down";
    }
    if (data->input.keyLeft.pressed) {
        return "left";
    }
    if (data->input.keyRight.pressed) {
        return "right";
    }
    if (data->input.keyX.pressed) {
        return "attack";
    }
    return "none";
}

std::string GameScene::getAIAction() {
    auto acts =
        std::vector<std::string>{"up", "down", "left", "right", "attack"};
    for (int i = 0; i < 50; i++) {
        acts.emplace_back("none");
    }
    std::uniform_int_distribution<> dist(0, acts.size() - 1);
    return acts[dist(engine)];
}

std::tuple<int, int> GameScene::getEnablePos() {
    std::vector<std::tuple<int, int>> pos;
    for (int x = 0; x < Config::BOARD_WIDTH; x++) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            if (board.getState(x, y) == Board::State::ENABLE) {
                pos.emplace_back(x, y);
            }
        }
    }
    std::shuffle(pos.begin(), pos.end(), engine);
    return pos.front();
}

bool GameScene::isFinish() {
    int cnt = std::count_if(
        players.begin(), players.end(),
        [](const Player &player) { return player.getRemainingPlayers() == 0; });
    return cnt >= 3;
}

void GameScene::draw() noexcept {
    using NCursesUtil::refresh;
    using NCursesUtil::Color;

    auto colors = std::vector<Color>{Color::DARK_RED,     Color::SUB_RED,
                                     Color::DARK_YELLOW,  Color::SUB_YELLOW,
                                     Color::DARK_MAGENTA, Color::SUB_MAGENTA,
                                     Color::DARK_BLUE,    Color::SUB_BLUE};

    for (int x = 0; x < Config::BOARD_WIDTH; x++) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            int v = x + y * Config::BOARD_HEIGHT;
            int nx = (v & 0xf) >> 1;
            int ny = v >> 5;

            auto state = board.getState(x, y);
            int id = board.getAttackedId(x, y);
            switch (state) {
                case Board::State::ENABLE:
                    if ((nx + ny) % 2 == 0)
                        drawCell(Color::GREEN, x, y);
                    else
                        drawCell(Color::SUB_GREEN, x, y);

                    break;
                case Board::State::UNSTABLE:
                    if ((nx + ny) % 2 == 0)
                        drawCell(colors[id * 2], x, y);
                    else
                        drawCell(colors[id * 2 + 1], x, y);
                    break;
                case Board::State::DISABLE:
                    drawCell(Color::BLACK, x, y);
                    break;
            }
        }
    }
    colors = std::vector<Color>{Color::RED, Color::YELLOW, Color::MAGENTA,
                                Color::CYAN};
    for (int i = 0; i < players.size(); i++) {
        auto &player = players[i];
        if (!player.died()) {
            drawPlayer(colors[i], player.getX(), player.getY(),
                       player.getDirection());
        }
        drawPlayerInfo(i);
    }

    refresh();
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

void GameScene::drawPlayer(NCursesUtil::Color color, int x, int y,
                           Direction dir) {
    using NCursesUtil::drawDot;
    using NCursesUtil::drawCursor;
    using NCursesUtil::Color;
    assert(0 <= x && x < Config::BOARD_WIDTH);
    assert(0 <= y && y < Config::BOARD_HEIGHT);

    for (int dx = 0; dx < CELL_LENGTH; dx++) {
        for (int dy = 0; dy < CELL_LENGTH; dy++) {
            int nx = CELL_LENGTH * x + OFFSET_X + dx;
            int ny = CELL_LENGTH * y + OFFSET_Y + dy;
            drawDot(color, nx, ny);
        }
    }
    switch (dir) {
        case Direction::UP:
            drawCursor(Color::BLACK, 2 * (CELL_LENGTH * x + OFFSET_X) + 2,
                       CELL_LENGTH * y + OFFSET_Y);
            drawCursor(Color::BLACK, 2 * (CELL_LENGTH * x + OFFSET_X) + 3,
                       CELL_LENGTH * y + OFFSET_Y);

            break;
        case Direction::DOWN:
            drawCursor(Color::BLACK, 2 * (CELL_LENGTH * x + OFFSET_X) + 2,
                       CELL_LENGTH * y + OFFSET_Y + 2);
            drawCursor(Color::BLACK, 2 * (CELL_LENGTH * x + OFFSET_X) + 3,
                       CELL_LENGTH * y + OFFSET_Y + 2);
            break;
        case Direction::LEFT:
            drawCursor(Color::BLACK, 2 * (CELL_LENGTH * x + OFFSET_X),
                       CELL_LENGTH * y + OFFSET_Y + 1);
            break;
        case Direction::RIGHT:
            drawCursor(Color::BLACK,
                       2 * (CELL_LENGTH * x + OFFSET_X) + 2 * CELL_LENGTH - 1,
                       CELL_LENGTH * y + OFFSET_Y + 1);
            break;
    }
}
void GameScene::drawPlayerInfo(int idx) {
    using NCursesUtil::drawString;
    auto name = players[idx].getName();
    int remainingPlayers = players[idx].getRemainingPlayers();
    drawString(2 * CELL_LENGTH * Config::BOARD_WIDTH + 10, 10 + idx * 10,
               name + ": " + std::to_string(remainingPlayers));
}
}  // namespace oti_oti_fight
