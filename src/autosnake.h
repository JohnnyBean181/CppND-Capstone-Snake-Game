#ifndef AUTOSNAKE_H
#define AUTOSNAKE_H

#include "snake.h"

class AutoSnake : public Snake {

public:

    AutoSnake(int grid_width, int grid_height)
        : Snake(grid_width, grid_height){};

    // by calling this func,
    // auto snake knows how to walk around the panel.
    void Redirect(SDL_Point food);

    // turn the direction to the left
    void TurnLeft();


private:
    int grid_width;
    int grid_height;
};

#endif