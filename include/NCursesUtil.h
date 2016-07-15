/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_NCURSESUTIL_H_
#define INCLUDE_NCURSESUTIL_H_

#include <string>

namespace oti_oti_fight {
namespace NCursesUtil {
void init();
void drawString(int x, int y, const std::string &str);
int getWidth();
int getHeight();
}  // namespace NCursesUtil
}  // namespace oti_oti_fight

#endif  // INCLUDE_NCURSESUTIL_H_
