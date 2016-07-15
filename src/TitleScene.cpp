/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <cstdlib>

#include "TitleScene.h"
#include "NCursesUtil.h"

namespace oti_oti_fight {
void TitleScene::init() noexcept {}

void TitleScene::update() noexcept {
    if (data->input.keyDown.pressed) {
        data->isSoroPlay = false;
    }
    if (data->input.keyUp.pressed) {
        data->isSoroPlay = true;
    }
    if (data->input.keyEnter.pressed) {
    }
}

void TitleScene::draw() noexcept {
    using NCursesUtil::drawString;
    using NCursesUtil::getHeight;
    using NCursesUtil::getWidth;

    int y = getHeight(), x = getWidth();
    auto getMaker = [](bool isSoroPlay) {
        return isSoroPlay ? std::string("> ") : std::string("  ");
    };
    bool isSoroPlay = data->isSoroPlay;
    std::string title = "おちおちファイト";
    std::string soroPlay = "ひとりで遊ぶ";
    std::string multiPlay = "みんなで遊ぶ";
    clear();

    drawString(x / 2, y / 2 - 10, title);
    drawString(x / 2, y / 2 + 5, getMaker(isSoroPlay) + soroPlay);
    drawString(x / 2, y / 2 + 7, getMaker(!isSoroPlay) + multiPlay);

    refresh();
}
}  // namespace oti_oti_fight
