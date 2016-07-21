/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_NCURSESUTIL_H_
#define INCLUDE_NCURSESUTIL_H_

#include <string>

namespace oti_oti_fight {
namespace NCursesUtil {

// SUB_ は減色？された色
enum struct Color {
    BLACK = 1,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    SUB_BLACK,
    SUB_RED,
    SUB_GREEN,
    SUB_YELLOW,
    SUB_BLUE,
    SUB_MAGENTA,
    SUB_CYAN,
    SUB_WHITE,
    SIZE = SUB_WHITE,
    DARK_RED = 53,
    DARK_YELLOW = 215,
    DARK_MAGENTA = 54,
    DARK_BLUE = 18
};

void init();
void drawString(int x, int y, const std::string &str, Color = Color::BLACK);
int getWidth();
int getHeight();

void changeColor(Color color);

// (x, y) の属するドットにcolorで点を打つ
void drawDot(Color color, int x, int y);

void drawCursor(Color color, int x, int y);

void clear();

void refresh();

}  // namespace NCursesUtil
}  // namespace oti_oti_fight

#endif  // INCLUDE_NCURSESUTIL_H_
