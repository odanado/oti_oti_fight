/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_
namespace oti_oti_fight {
class Player {
 public:
    enum struct Move { UP, DOWN, LEFT, RIGHT, ATTACK, NONE };
    Player(int x, int y, int remainingPlayers = 5);
    int getX(void) const { return x; }
    int getY(void) const { return y; }
    int getRemainingPlayers(void) { return remainingPlayers; }
    bool died(void) const { return remainingPlayers == 0; }

    void move(Move);

 private:
    void normalizePos(void);
    int x, y;
    int remainingPlayers;
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_PLAYER_H_
