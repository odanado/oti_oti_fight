/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_TITLESCENE_H_
#define INCLUDE_TITLESCENE_H_

#include <ncurses.h>

#include "SceneManager.h"

namespace oti_oti_fight {
class TitleScene : public MyApp::Scene {
    void init() noexcept override;
    void update() noexcept override;
    void draw() noexcept override;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_TITLESCENE_H_
