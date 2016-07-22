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
void init_color(Color color) {
    int c = static_cast<int>(color);
    init_pair(c, COLOR_WHITE, c);
}
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
#ifdef __linux__
    system("resize -s 55 170");
#endif
    for (int i = 0; i < static_cast<int>(Color::SIZE); i++) {
        init_pair(i + 1, COLOR_WHITE, i);
    }
    init_color(Color::DARK_RED);
    init_color(Color::DARK_YELLOW);
    init_color(Color::DARK_MAGENTA);
    init_color(Color::DARK_BLUE);
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
    drawCursor(color, 2 * x, y);
    drawCursor(color, 2 * x + 1, y);
}

void drawCursor(Color color, int x, int y) {
    changeColor(color);
    mvprintw(y, x, " ");
}

void clear() { ::clear(); }

void refresh() { ::refresh(); }

}  // namespace NCursesUtil
}  // namespace oti_oti_fight
