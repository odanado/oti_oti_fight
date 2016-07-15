/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
*/

#ifndef INCLUDE_SCENEBASE_H_
#define INCLUDE_SCENEBASE_H_

#include <memory>

namespace oti_oti_fight {
template <class State, class Data>
class SceneManager;

template <typename State, class Data>
class SceneBase {
 public:
    using Manager_t = SceneManager<State, Data>;

    virtual void init() noexcept = 0;
    virtual void update() noexcept = 0;
    virtual void draw() noexcept = 0;

    void setData(Manager_t *manager, const std::shared_ptr<Data> &data) {
        this->manager = manager;
        this->data = data;
    }

 protected:
    std::shared_ptr<Data> data;
    bool changeScene(const State &state) { return manager->changeScene(state); }

 private:
    Manager_t *manager = nullptr;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_SCENEBASE_H_
