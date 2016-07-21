/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <algorithm>

#include "ResultScene.h"
#include "NCursesUtil.h"

namespace oti_oti_fight {
using NCursesUtil::clear;
using NCursesUtil::drawString;
void ResultScene::init() noexcept { clear(); }
void ResultScene::update() noexcept {}
void ResultScene::draw() noexcept {
    auto rank = data->rank;
    std::reverse(rank.begin(), rank.end());

    for (int i = 0; i < rank.size(); i++) {
        drawString(55, 10 + i * 5, rank[i]);
    }
}
}  // namespace oti_oti_fight
