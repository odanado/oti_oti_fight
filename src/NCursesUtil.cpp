/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <ncurses.h>
#include <locale.h>

#include <string>

#include "NCursesUtil.h"

namespace oti_oti_fight {
namespace NCursesUtil {
void init() {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    crmode();
    noecho();
    curs_set(0);
    timeout(0);
}
void drawString(int x, int y, const std::string &str) {
    mvprintw(y, x - str.size() / 2, "%s", str.c_str());
}

int getWidth() {
    int y, x;
    getmaxyx(stdscr, y, x);
    return x;
}

int getHeight() {
    int y, x;
    getmaxyx(stdscr, y, x);
    return y;
}
}  // namespace NCursesUtil
}  // namespace oti_oti_fight
