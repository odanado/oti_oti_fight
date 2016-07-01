/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include "Player.h"
#include "Config.h"
#include "gtest/gtest.h"

class TestPlayer : public ::testing::Test {
 protected:
    using Player = oti_oti_fight::Player;
    using Move = Player::Move;
    virtual void SetUp() {}
};

TEST_F(TestPlayer, moveRight) {
    auto width = oti_oti_fight::Config::BOARD_WIDTH;
    auto player = Player("test", 0, 0);

    player.move(Move::RIGHT);
    EXPECT_EQ(player.getX(), 1);

    player = Player("test", width - 2, 0);
    player.move(Move::RIGHT);
    EXPECT_EQ(player.getX(), width - 1);
    player.move(Move::RIGHT);
    EXPECT_EQ(player.getX(), width - 1);
}

TEST_F(TestPlayer, moveLeft) {
    auto width = oti_oti_fight::Config::BOARD_WIDTH;
    auto player = Player("test", 1, 0);

    player.move(Move::LEFT);
    EXPECT_EQ(player.getX(), 0);
    player.move(Move::LEFT);
    EXPECT_EQ(player.getX(), 0);

    player = Player("test", width - 1, 0);
    player.move(Move::LEFT);
    EXPECT_EQ(player.getX(), width - 2);
}

TEST_F(TestPlayer, moveUp) {
    auto height = oti_oti_fight::Config::BOARD_HEIGHT;
    auto player = Player("test", 0, 1);

    player.move(Move::UP);
    EXPECT_EQ(player.getY(), 0);
    player.move(Move::UP);
    EXPECT_EQ(player.getY(), 0);

    player = Player("test", 0, height - 1);
    player.move(Move::UP);
    EXPECT_EQ(player.getY(), height - 2);
}

TEST_F(TestPlayer, moveDown) {
    auto height = oti_oti_fight::Config::BOARD_HEIGHT;
    auto player = Player("test", 0, 0);

    player.move(Move::DOWN);
    EXPECT_EQ(player.getY(), 1);

    player = Player("test", 0, height - 2);
    player.move(Move::DOWN);
    EXPECT_EQ(player.getY(), height - 1);
    player.move(Move::DOWN);
    EXPECT_EQ(player.getY(), height - 1);
}

TEST_F(TestPlayer, moveAttack) {
    // TODO(odanado): atode
}
