/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <cstdlib>

#include "TitleScene.h"
#include "NCursesUtil.h"

namespace oti_oti_fight {
using NCursesUtil::drawString;
using NCursesUtil::getHeight;
using NCursesUtil::getWidth;
using NCursesUtil::clear;
using NCursesUtil::refresh;

void TitleScene::init() noexcept { data->isFinish = false; }

void TitleScene::update() noexcept {
    if (data->input.keyDown.pressed) {
        data->isSoroPlay = false;
    }
    if (data->input.keyUp.pressed) {
        data->isSoroPlay = true;
    }
    if (data->input.keyEnter.pressed) {
        if (data->isSoroPlay) {
            changeScene("Game");
        } else {
            data->isFinish = true;
            clear();
        }
    }
}

void TitleScene::draw() noexcept {
    int y = getHeight(), x = getWidth();
    auto getMaker = [](bool marker) {
        return marker ? std::string("> ") : std::string("  ");
    };
    bool isSoroPlay = data->isSoroPlay;
    std::string title = "おちおちファイト";
    std::string soroPlay = "ひとりで遊ぶ";
    std::string exit = "終わる";
    clear();

    drawString(x / 2, y / 2 - 10, title);
    drawString(x / 2, y / 2 + 5, getMaker(isSoroPlay) + soroPlay);
    drawString(x / 2, y / 2 + 7, getMaker(!isSoroPlay) + exit);

    refresh();
}
}  // namespace oti_oti_fight
