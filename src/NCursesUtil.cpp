/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <ncurses.h>
#include <locale.h>

#include <string>
#include <cstdlib>

#include "NCursesUtil.h"

namespace oti_oti_fight {
namespace NCursesUtil {
void init() {
    setenv("TERM", "xterm-256color", 1);
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    crmode();
    noecho();
    curs_set(0);
    timeout(0);
    for (int i = 0; i < static_cast<int>(Color::SIZE); i++) {
        init_pair(i + 1, COLOR_WHITE, i);
    }
}
void drawString(int x, int y, const std::string &str, Color color) {
    changeColor(color);
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

void changeColor(Color color) { attron(COLOR_PAIR(static_cast<int>(color))); }
void drawDot(Color color, int x, int y) {
    changeColor(color);
    mvprintw(y, 2 * x, "  ");
}

void clear() { ::clear(); }

void refresh() { ::refresh(); }

}  // namespace NCursesUtil
}  // namespace oti_oti_fight
