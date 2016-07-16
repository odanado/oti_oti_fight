/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include "Player.h"
#include "Config.h"
#include "Direction.h"
#include "gtest/gtest.h"

class TestPlayer : public ::testing::Test {
 protected:
    using Player = oti_oti_fight::Player;
    virtual void SetUp() {}
};

TEST_F(TestPlayer, moveRight) {
    using oti_oti_fight::Direction;
    auto width = oti_oti_fight::Config::BOARD_WIDTH;
    auto player = Player("test", 0, 0, Direction::LEFT);

    player.move(Direction::RIGHT);
    EXPECT_EQ(player.getX(), 1);

    player = Player("test", width - 2, 0, Direction::LEFT);
    player.move(Direction::RIGHT);
    EXPECT_EQ(player.getX(), width - 1);
    player.move(Direction::RIGHT);
    EXPECT_EQ(player.getX(), width - 1);
}

TEST_F(TestPlayer, moveLeft) {
    using oti_oti_fight::Direction;
    auto width = oti_oti_fight::Config::BOARD_WIDTH;
    auto player = Player("test", 1, 0, Direction::RIGHT);

    player.move(Direction::LEFT);
    EXPECT_EQ(player.getX(), 0);
    player.move(Direction::LEFT);
    EXPECT_EQ(player.getX(), 0);

    player = Player("test", width - 1, 0, Direction::RIGHT);
    player.move(Direction::LEFT);
    EXPECT_EQ(player.getX(), width - 2);
}

TEST_F(TestPlayer, moveUp) {
    using oti_oti_fight::Direction;
    auto height = oti_oti_fight::Config::BOARD_HEIGHT;
    auto player = Player("test", 0, 1, Direction::UP);

    player.move(Direction::UP);
    EXPECT_EQ(player.getY(), 0);
    player.move(Direction::UP);
    EXPECT_EQ(player.getY(), 0);

    player = Player("test", 0, height - 1, Direction::UP);
    player.move(Direction::UP);
    EXPECT_EQ(player.getY(), height - 2);
}

TEST_F(TestPlayer, moveDown) {
    using oti_oti_fight::Direction;
    auto height = oti_oti_fight::Config::BOARD_HEIGHT;
    auto player = Player("test", 0, 0, Direction::UP);

    player.move(Direction::DOWN);
    EXPECT_EQ(player.getY(), 1);

    player = Player("test", 0, height - 2, Direction::UP);
    player.move(Direction::DOWN);
    EXPECT_EQ(player.getY(), height - 1);
    player.move(Direction::DOWN);
    EXPECT_EQ(player.getY(), height - 1);
}

TEST_F(TestPlayer, moveAttack) {
    // TODO(odanado): atode
}
