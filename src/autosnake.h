#ifndef AUTOSNAKE_H
#define AUTOSNAKE_H

#include "snake.h"

class AutoSnake : public Snake {

public:

    AutoSnake(int grid_width, int grid_height)
        : Snake(grid_width, grid_height){
        // identify itself as robot snake.
        // so render knows not to draw particles.
        solo = false;
    }

    // by calling this func,
    // auto snake knows how to walk around the panel.
    void Redirect();

    // turn the direction to the left
    void TurnLeft();


private:
    int grid_width;
    int grid_height;
};

#endif