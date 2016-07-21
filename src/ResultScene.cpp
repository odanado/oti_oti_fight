/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <algorithm>
#include <cstdio>

#include "ResultScene.h"
#include "NCursesUtil.h"
#include "Timer.h"

namespace oti_oti_fight {
using NCursesUtil::clear;
using NCursesUtil::drawString;
void ResultScene::init() noexcept {
    clear();
    auto now = Timer::now<Timer::milliseconds>();
    std::string fileName = "log/" + std::to_string(now.count()) + ".txt";
    FILE* fp = fopen(fileName.c_str(), "w");
    for (int i = 0; i < data->log.size(); i++) {
        fprintf(fp, "%s\n", data->log[i].c_str());
    }
    fclose(fp);
}
void ResultScene::update() noexcept {}
void ResultScene::draw() noexcept {
    auto rank = data->rank;
    std::reverse(rank.begin(), rank.end());

    for (int i = 0; i < rank.size(); i++) {
        drawString(55, 10 + i * 5, rank[i]);
    }
}
}  // namespace oti_oti_fight
