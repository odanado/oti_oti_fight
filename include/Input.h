/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_INPUT_H_
#define INCLUDE_INPUT_H_
namespace oti_oti_fight {
class Input {
    struct Key {
        bool pressed;
        bool released;
        Key() : pressed(false), released(false) {}
    };

 public:
    Input();
    void operator()();

    Key keyUp;
    Key keyDown;
    Key keyRight;
    Key keyLeft;
    Key keyX;
    Key keyEnter;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_INPUT_H_
