/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <ncurses.h>
#include <locale.h>

#include "NCursesUtil.h"
#include "Input.h"

namespace oti_oti_fight {
Input::Input() {
    using NCursesUtil::init;
    init();
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
