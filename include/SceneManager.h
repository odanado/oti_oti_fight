/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
*/

#ifndef INCLUDE_SCENEMANAGER_H_
#define INCLUDE_SCENEMANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <boost/optional.hpp>

#include "SceneBase.h"

namespace oti_oti_fight {

template <class State, class Data = void>
class SceneManager {
 private:
    using Scene_t = std::shared_ptr<SceneBase<State, Data>>;
    using FactoryFunction_t = std::function<Scene_t()>;

    std::unordered_map<State, FactoryFunction_t> factories;
    std::shared_ptr<Data> data;

    Scene_t currentScene;

    State currentState;

    boost::optional<State> firstState;

 public:
    using Scene = SceneBase<State, Data>;

    explicit SceneManager(
        const std::shared_ptr<Data> &data = std::make_shared<Data>())
        : data(data) {}

    template <class Scene>
    bool add(const State &state) {
        if (factories.count(state)) {
            return false;
        }

        factories.emplace(state, [&]() {
            auto m = std::make_shared<Scene>();
            m->setData(this, data);
            return m;
        });

        if (!firstState) {
            firstState = state;
        }

        return true;
    }

    bool init(const State &state) {
        if (currentScene) {
            return false;
        }

        auto it = factories.find(state);
        if (it == factories.end()) {
            return false;
        }

        currentState = state;
        currentScene = it->second();
        currentScene->init();
        return true;
    }

    bool update() {
        if (!currentScene) {
            if (!firstState) {
                return true;
            } else if (!init(firstState.get())) {
                return false;
            }
        }

        currentScene->update();
        return true;
    }

    void draw() {
        if (!currentScene) {
            return;
        }
        currentScene->draw();
    }

    bool updateAndDraw() {
        if (update()) {
            draw();
            return true;
        }

        return false;
    }

    bool changeScene(const State &state) {
        if (!factories.count(state)) {
            return false;
        }
        currentScene = factories[state]();
        currentState = state;
        currentScene->init();
        return true;
    }
    std::shared_ptr<Data> get() { return data; }
    State getState() { return currentState; }
};

}  // namespace oti_oti_fight
#endif  // INCLUDE_SCENEMANAGER_H_
