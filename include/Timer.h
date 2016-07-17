/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include <chrono>

namespace oti_oti_fight {
namespace Timer {
using std::chrono::system_clock;
using std::chrono::duration_cast;
using milliseconds = std::chrono::milliseconds;
using microseconds = std::chrono::microseconds;

void update();

template <class T>
T now();

template <>
milliseconds now();

template <>
microseconds now();

}  // namespace Timer
}  // namespace oti_oti_fight
#endif  // INCLUDE_TIMER_H_
