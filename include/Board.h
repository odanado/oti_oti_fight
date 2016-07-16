/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

#include <array>
#include <tuple>
#include <chrono>
#include <cassert>

#include "Config.h"
#include "Direction.h"

namespace oti_oti_fight {
class Board {
 public:
    /**
     * @enum State
     * ボードの状態を表す
     * ENABLE: 移動可能な状態
     * DISABLE: 落下した状態
     * UNSTABLE: 落下対象になった状態
     */
    enum struct State { ENABLE, DISABLE, UNSTABLE };

    Board();

    /**
     * @function attack
     * 攻撃をする．ボードの状態が変化する
     * @id: 攻撃したプレイヤーID
     * @x: 攻撃したマス目のx
     * @y: 攻撃したマス目のy
     * @dir: 攻撃した方向
     */
    void attack(int id, int x, int y, Direction dir);
    void update();

    State getState(int x, int y) const {
        assert(0 <= x && x < Config::BOARD_WIDTH);
        assert(0 <= y && y < Config::BOARD_HEIGHT);
        return board[y][x];
    }

    int getAttackedId(int x, int y) const {
        assert(0 <= x && x < Config::BOARD_WIDTH);
        assert(0 <= y && y < Config::BOARD_HEIGHT);
        return std::get<0>(unstableBoard[y][x]);
    }

 private:
    using millisec = std::chrono::milliseconds;
    template <class T>
    using BoardBase =
        std::array<std::array<T, Config::BOARD_WIDTH>, Config::BOARD_HEIGHT>;
    BoardBase<State> board;
    // <id, 落下までの時間>
    BoardBase<std::tuple<int, std::int64_t>> unstableBoard;

    // 落下した時間
    BoardBase<std::int64_t> disableBoard;

    void attackImpl(int id, int x, int y, int dx, int dy);
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_BOARD_H_
