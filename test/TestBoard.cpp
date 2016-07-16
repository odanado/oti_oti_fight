/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include "Board.h"
#include "gtest/gtest.h"

namespace oti_oti_fight {
class TestBoard : public ::testing::Test {
 protected:
    virtual void SetUp() {}
};

TEST_F(TestBoard, attackRight) {
    auto test = [](const Board &board) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            for (int x = 0; x < Config::BOARD_WIDTH; x++) {
                int v = x + y * Config::BOARD_HEIGHT;
                int nx = (v & 0xf) >> 1;
                int ny = v >> 5;
                if (ny == 3) {
                    if (nx <= 3) {
                        EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), -1);
                    } else {
                        EXPECT_EQ(board.getState(x, y), Board::State::UNSTABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), 0);
                    }
                } else {
                    EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                    EXPECT_EQ(board.getAttackedId(x, y), -1);
                }
            }
        }
    };
    Board board;
    board.attack(0, 6, 6, Direction::RIGHT);
    test(board);

    board = Board();
    board.attack(0, 6, 7, Direction::RIGHT);
    test(board);

    board = Board();
    board.attack(0, 7, 6, Direction::RIGHT);
    test(board);

    board = Board();
    board.attack(0, 7, 7, Direction::RIGHT);
    test(board);
}
TEST_F(TestBoard, attackLeft) {
    auto test = [](const Board &board) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            for (int x = 0; x < Config::BOARD_WIDTH; x++) {
                int v = x + y * Config::BOARD_HEIGHT;
                int nx = (v & 0xf) >> 1;
                int ny = v >> 5;
                if (ny == 3) {
                    if (nx >= 3) {
                        EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), -1);
                    } else {
                        EXPECT_EQ(board.getState(x, y), Board::State::UNSTABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), 0);
                    }
                } else {
                    EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                    EXPECT_EQ(board.getAttackedId(x, y), -1);
                }
            }
        }
    };
    Board board;
    board.attack(0, 6, 6, Direction::LEFT);
    test(board);

    board = Board();
    board.attack(0, 7, 6, Direction::LEFT);
    test(board);

    board = Board();
    board.attack(0, 6, 7, Direction::LEFT);
    test(board);

    board = Board();
    board.attack(0, 7, 7, Direction::LEFT);
    test(board);
}
TEST_F(TestBoard, attackUp) {
    auto test = [](const Board &board) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            for (int x = 0; x < Config::BOARD_WIDTH; x++) {
                int v = x + y * Config::BOARD_HEIGHT;
                int nx = (v & 0xf) >> 1;
                int ny = v >> 5;
                if (nx == 3) {
                    if (ny >= 3) {
                        EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), -1);
                    } else {
                        EXPECT_EQ(board.getState(x, y), Board::State::UNSTABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), 0);
                    }
                } else {
                    EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                    EXPECT_EQ(board.getAttackedId(x, y), -1);
                }
            }
        }
    };
    Board board;
    board.attack(0, 6, 6, Direction::UP);
    test(board);

    board = Board();
    board.attack(0, 7, 6, Direction::UP);
    test(board);

    board = Board();
    board.attack(0, 6, 7, Direction::UP);
    test(board);

    board = Board();
    board.attack(0, 7, 7, Direction::UP);
    test(board);
}
TEST_F(TestBoard, attackDown) {
    auto test = [](const Board &board) {
        for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
            for (int x = 0; x < Config::BOARD_WIDTH; x++) {
                int v = x + y * Config::BOARD_HEIGHT;
                int nx = (v & 0xf) >> 1;
                int ny = v >> 5;
                if (nx == 3) {
                    if (ny <= 3) {
                        EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), -1);
                    } else {
                        EXPECT_EQ(board.getState(x, y), Board::State::UNSTABLE);
                        EXPECT_EQ(board.getAttackedId(x, y), 0);
                    }
                } else {
                    EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                    EXPECT_EQ(board.getAttackedId(x, y), -1);
                }
            }
        }
    };
    Board board;
    board.attack(0, 6, 6, Direction::DOWN);
    test(board);

    board = Board();
    board.attack(0, 7, 6, Direction::DOWN);
    test(board);

    board = Board();
    board.attack(0, 6, 7, Direction::DOWN);
    test(board);

    board = Board();
    board.attack(0, 7, 7, Direction::DOWN);
    test(board);
}
TEST_F(TestBoard, multiAttack) {
    Board board;
    board.attack(0, 0, 0, Direction::RIGHT);
    board.attack(1, 6, 6, Direction::UP);
    for (int y = 0; y < Config::BOARD_HEIGHT; y++) {
        for (int x = 0; x < Config::BOARD_WIDTH; x++) {
            int v = x + y * Config::BOARD_HEIGHT;
            int nx = (v & 0xf) >> 1;
            int ny = v >> 5;
            if (nx == 3 && ny < 3) {
                EXPECT_EQ(board.getState(x, y), Board::State::UNSTABLE);
                EXPECT_EQ(board.getAttackedId(x, y), 1);
            } else if (ny == 0 && 0 < nx) {
                EXPECT_EQ(board.getState(x, y), Board::State::UNSTABLE);
                EXPECT_EQ(board.getAttackedId(x, y), 0);
            } else {
                EXPECT_EQ(board.getState(x, y), Board::State::ENABLE);
                EXPECT_EQ(board.getAttackedId(x, y), -1);
            }
        }
    }
}
}  // namespace oti_oti_fight
