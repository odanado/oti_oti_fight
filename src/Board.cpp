/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <chrono>
#include <cassert>
#include <iostream>

#include "Board.h"

namespace oti_oti_fight {
Board::Board() {
    for (int i = 0; i < board.size(); i++) {
        board[i].fill(State::ENABLE);
        unstableBoard[i].fill(std::make_tuple(-1, -1));
        disableBoard[i].fill(-1);
    }
}

void Board::attack(int id, int x, int y, Direction dir) {
    assert(0 <= id && id < 4);
    assert(0 <= x && x < Config::BOARD_WIDTH);
    assert(0 <= y && y < Config::BOARD_HEIGHT);
    int dx, dy;
    switch (dir) {
        case Direction::UP:
            dx = 0;
            dy = -1;
            y -= 1 + (y % 2 != 0);
            break;
        case Direction::DOWN:
            dx = 0;
            dy = 1;
            y += 1 + (y % 2 == 0);
            break;
        case Direction::LEFT:
            dx = -1;
            dy = 0;
            x -= 1 + (x % 2 != 0);
            break;
        case Direction::RIGHT:
            dx = 1;
            dy = 0;
            x += 1 + (x % 2 == 0);
            break;
    }
    auto now = std::chrono::system_clock::now();
    attackImpl(id, x, y, dx, dy, now);
    if (dir == Direction::RIGHT || dir == Direction::LEFT) {
        if (y % 2 == 0) {
            attackImpl(id, x, y + 1, dx, dy, now);
        } else {
            attackImpl(id, x, y - 1, dx, dy, now);
        }
    } else {
        if (x % 2 == 0) {
            attackImpl(id, x + 1, y, dx, dy, now);
        } else {
            attackImpl(id, x - 1, y, dx, dy, now);
        }
    }
}

void Board::attackImpl(int id, int x, int y, int dx, int dy,
                       const std::chrono::system_clock::time_point &now) {
    using std::chrono::duration_cast;

    auto time = now + millisec(Config::FALL_UNTIL_TIME);
    while (0 <= x && x < Config::BOARD_WIDTH && 0 <= y &&
           y < Config::BOARD_HEIGHT) {
        // 落下までの時間は上書きされないが，マスの色情報は更新される
        std::get<0>(unstableBoard[y][x]) = id;
        if (board[y][x] == State::ENABLE) {
            board[y][x] = State::UNSTABLE;
            unstableBoard[y][x] = std::make_tuple(
                id, duration_cast<millisec>(time.time_since_epoch()).count());
        }
        if ((dx && x % 2 == 1) || (dy && y % 2 == 1))
            time += millisec(Config::FALL_INCRESE_TIME);
        x += dx;
        y += dy;
    }
}
void Board::update() {
    using std::chrono::system_clock;
    using std::chrono::duration_cast;

    auto now = system_clock::now().time_since_epoch();
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[y].size(); x++) {
            if (board[y][x] == State::DISABLE) {
                auto time = millisec(disableBoard[y][x]);
                if (time < duration_cast<millisec>(now)) {
                    board[y][x] = State::ENABLE;
                    disableBoard[y][x] = -1;
                }
            } else if (board[y][x] == State::UNSTABLE) {
                auto time = millisec(std::get<1>(unstableBoard[y][x]));
                if (time < duration_cast<millisec>(now)) {
                    board[y][x] = State::DISABLE;
                    unstableBoard[y][x] = std::make_tuple(-1, -1);
                    disableBoard[y][x] =
                        duration_cast<millisec>(
                            now + millisec(Config::ENABLE_UNTIL_TIME))
                            .count();
                }
            }
        }
    }
}

}  // namespace oti_oti_fight
