/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */
#include <string>
#include "SceneManager.h"
#include "gtest/gtest.h"

class TestSceneManager : public ::testing::Test {
 protected:
    struct GameData {
        int t;
    };
    using MyApp = oti_oti_fight::SceneManager<std::string, GameData>;

    struct Title : public MyApp::Scene {
        void init() noexcept override {}
        void update() noexcept override {
            if (data->t == 5) changeScene("Game");
            data->t++;
        }
        void draw() noexcept override {}
    };
    struct Game : public MyApp::Scene {
        void init() noexcept override {}
        void update() noexcept override {}
        void draw() noexcept override {}
    };
    virtual void SetUp() {}
};
TEST_F(TestSceneManager, init) {
    MyApp manager;
    manager.add<Title>("Title");
    manager.add<Game>("Game");
    manager.init("Game");
    EXPECT_EQ(manager.getState(), "Game");
}

TEST_F(TestSceneManager, changeScene) {
    MyApp manager;
    manager.add<Title>("Title");
    manager.add<Game>("Game");
    manager.changeScene("Game");
    EXPECT_EQ(manager.getState(), "Game");
}

TEST_F(TestSceneManager, update) {
    MyApp manager;
    manager.add<Title>("Title");
    manager.add<Game>("Game");
    manager.update();
    manager.update();
    manager.update();
    manager.update();
    manager.update();
    EXPECT_EQ(manager.get()->t, 5);
    manager.update();
    EXPECT_EQ(manager.getState(), "Game");
}
