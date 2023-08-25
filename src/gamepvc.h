#ifndef GAMEPVC_H
#define GAMEPVC_H

#include <random>
#include <memory>
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "resource.h"
#include "autosnake.h"
#include "game.h"

class GamePvC : public Game {

public:

    GamePvC(std::size_t grid_width, std::size_t grid_height);
    std::string Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration);
    int GetScore2() const;

private:
    void Update();
    std::unique_ptr<AutoSnake> _snake_robot;
    // score of the 2nd snake
    int score2{0};
};

#endif