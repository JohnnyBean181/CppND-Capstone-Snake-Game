#ifndef AUTOSNAKE_H
#define AUTOSNAKE_H

#include "snake.h"

class AutoSnake : public Snake {

public:
    void Redirect();

    // turn the direction to the left
    void TurnLeft();
};

#endif