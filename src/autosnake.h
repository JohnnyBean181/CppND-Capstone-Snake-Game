#ifndef AUTOSNAKE_H
#define AUTOSNAKE_H

#include "snake.h"

class AutoSnake : public Snake {

public:

    AutoSnake(int grid_width, int grid_height)
        : Snake(grid_width, grid_height){};

    // by calling this func,
    // auto snake knows how to move.
    void Redirect(SDL_Point food);

    // turn direction to the left
    void TurnLeft();


private:
    int grid_width;
    int grid_height;
};

#endif