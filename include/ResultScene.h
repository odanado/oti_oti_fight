/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_RESULTSCENE_H_
#define INCLUDE_RESULTSCENE_H_

#include "SceneManager.h"

namespace oti_oti_fight {
class ResultScene : public MyApp::Scene {
 public:
    void init() noexcept override;
    void update() noexcept override;
    void draw() noexcept override;
};

}  // namespace oti_oti_fight
#endif  // INCLUDE_RESULTSCENE_H_
