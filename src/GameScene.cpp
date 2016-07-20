/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <vector>
#include <random>

#include "GameScene.h"
#include "NCursesUtil.h"
#include "Config.h"

namespace oti_oti_fight {
void GameScene::init() noexcept {
    using NCursesUtil::clear;
    clear();
    // TODO(odan): 乱数で初期の向きを決めるようにする
    players.resize(Config::PLAYERS);
    for (int i = 0; i < Config::PLAYERS; i++) {
        std::uniform_int_distribution<> distY(0, Config::BOARD_HEIGHT - 1);
        std::uniform_int_distribution<> distX(0, Config::BOARD_WIDTH - 1);
        std::uniform_int_distribution<> dist(0, 3);
        auto dir = static_cast<Direction>(dist(engine));
        players[i] = Player("player" + std::to_string(i), distX(engine),
                            distY(engine), dir);
    }
}

void GameScene::update() noexcept {
    for (int i = 0; i < players.size(); i++) {
        auto &player = players[i];
        if (player.died()) continue;
        int x = player.getX();
        int y = player.getY();
        if (!board.valid(x, y)) {
            player.fall();
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
        }
        auto valid = [&](int x, int y) {
            return board.valid(x, y) &&
                   board.getState(x, y) != Board::State::DISABLE;
        };
        if (act == "up" && valid(x, y - 1)) {
            player.move(Direction::UP);
        }
        if (act == "down" && valid(x, y + 1)) {
            player.move(Direction::DOWN);
        }
        if (act == "left" && valid(x - 1, y)) {
            player.move(Direction::LEFT);
        }
        if (act == "right" && valid(x + 1, y)) {
            player.move(Direction::RIGHT);
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
                    if ((nx + ny) % 2 == 0)
                        drawCell(Color::SUB_GREEN, x, y);
                    else
                        drawCell(Color::SUB_BLUE, x, y);
                    break;
                case Board::State::DISABLE:
                    drawCell(Color::BLACK, x, y);
                    break;
            }
        }
    }
    std::vector<Color> colors{Color::RED, Color::YELLOW, Color::MAGENTA,
                              Color::CYAN};
    for (int i = 0; i < players.size(); i++) {
        auto &player = players[i];
        if (player.died()) {
            drawPlayer(Color::SUB_BLACK, player.getX(), player.getY(),
                       player.getDirection());
        } else {
            drawPlayer(colors[i], player.getX(), player.getY(),
                       player.getDirection());
        }
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
}  // namespace oti_oti_fight
