/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include "SceneManager.h"
#include "TitleScene.h"

int main() {
    oti_oti_fight::MyApp manager;
    manager.add<oti_oti_fight::TitleScene>("Title");
    while (1) {
        manager.updateAndDraw();
    }
}
