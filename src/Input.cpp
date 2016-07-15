/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <ncurses.h>
#include <locale.h>

#include "Input.h"

namespace oti_oti_fight {
Input::Input() {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    crmode();
    noecho();
    curs_set(0);
    timeout(0);
}

void Input::operator()() {
    auto ch = getch();
    keyUp.pressed = ch == KEY_UP;
    keyDown.pressed = ch == KEY_DOWN;
    keyRight.pressed = ch == KEY_RIGHT;
    keyLeft.pressed = ch == KEY_LEFT;
    keyX.pressed = ch == 'x';
    keyEnter.pressed = ch == KEY_ENTER;
}
}  // namespace oti_oti_fight
