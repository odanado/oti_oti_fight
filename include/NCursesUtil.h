/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_NCURSESUTIL_H_
#define INCLUDE_NCURSESUTIL_H_

#include <string>

namespace oti_oti_fight {
namespace NCursesUtil {
enum struct Color { BLACK = 1, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

void init();
void drawString(int x, int y, const std::string &str, Color = Color::BLACK);
int getWidth();
int getHeight();

void changeColor(Color color);

// (x, y) の属するドットにcolorで点を打つ
void drawDot(Color color, int x, int y);

}  // namespace NCursesUtil
}  // namespace oti_oti_fight

#endif  // INCLUDE_NCURSESUTIL_H_
