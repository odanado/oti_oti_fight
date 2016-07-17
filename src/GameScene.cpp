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
    int x = player.getX();
    int y = player.getY();
    if (data->input.keyUp.pressed && board.valid(x, y - 1)) {
        player.move(Direction::UP);
    }
    if (data->input.keyDown.pressed && board.valid(x, y + 1)) {
        player.move(Direction::DOWN);
    }
    if (data->input.keyLeft.pressed && board.valid(x - 1, y)) {
        player.move(Direction::LEFT);
    }
    if (data->input.keyRight.pressed && board.valid(x + 1, y)) {
        player.move(Direction::RIGHT);
    }
    if (data->input.keyX.pressed) {
        board.attack(0, player.getX(), player.getY(), player.getDirection());
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
