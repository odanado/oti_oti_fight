/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include "Timer.h"

namespace oti_oti_fight {
namespace Timer {

auto now_ = system_clock::now().time_since_epoch();

void update() { now_ = system_clock::now().time_since_epoch(); }

template <>
milliseconds now() {
    return duration_cast<milliseconds>(now_);
}

template <>
microseconds now() {
    return duration_cast<microseconds>(now_);
}
}  // namespace Timer
}  // namespace oti_oti_fight
