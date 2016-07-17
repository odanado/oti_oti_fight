/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <chrono>
#include <thread>

#include "Timer.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

int main() {
    using std::chrono::system_clock;
    using std::literals::chrono_literals::operator""us;

    oti_oti_fight::MyApp manager;
    auto gameData = manager.get();
    manager.add<oti_oti_fight::TitleScene>("Title");
    manager.add<oti_oti_fight::GameScene>("Game");

    auto nextFrame = system_clock::now() + 16666us;

    while (1) {
        gameData->input();
        manager.update();
        oti_oti_fight::Timer::update();
        auto nowFrame = system_clock::now();
        if (nowFrame < nextFrame) {
            manager.draw();
            nowFrame = system_clock::now();
            if (nowFrame < nextFrame) {
                std::this_thread::sleep_for(nextFrame - nowFrame);
            }
        }

        nextFrame += 16666us;
    }
}
