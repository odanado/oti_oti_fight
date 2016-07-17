/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */
#include "GameScene.h"
#include "NCursesUtil.h"
#include "Config.h"

namespace oti_oti_fight {
void GameScene::init() noexcept {
    using NCursesUtil::clear;
    clear();
    // TODO(odan): 乱数で初期の向きを決めるようにする
    player = Player("test", 0, 0, Direction::RIGHT);
}

void GameScene::update() noexcept {
    if (data->input.keyUp.pressed) {
        player.move(Direction::UP);
    }
    if (data->input.keyDown.pressed) {
        player.move(Direction::DOWN);
    }
    if (data->input.keyLeft.pressed) {
        player.move(Direction::LEFT);
    }
    if (data->input.keyRight.pressed) {
        player.move(Direction::RIGHT);
    }
    if (data->input.keyX.pressed) {
        board.attack(0, player.getX(), player.getY(), player.getDirection());
    }
}

void GameScene::draw() noexcept {
    using NCursesUtil::refresh;
    using NCursesUtil::Color;

    for (int x = 0; x < Config::BOARD_WIDTH; x++) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            int v = x + y * Config::BOARD_HEIGHT;
            int nx = (v & 0xf) >> 1;
            int ny = v >> 5;

            if (board.getState(x, y) == Board::State::ENABLE) {
                if ((nx + ny) % 2 == 0)
                    drawCell(Color::GREEN, x, y);
                else
                    drawCell(Color::BLUE, x, y);
            } else {
                drawCell(Color::BLACK, x, y);
            }
        }
    }
    drawPlayer(Color::RED, player.getX(), player.getY());
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
