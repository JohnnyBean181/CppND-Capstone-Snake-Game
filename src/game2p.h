#ifndef GAME2P_H
#define GAME2P_H

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

class Game2P : public Game {

public:

    Game2P(std::size_t grid_width, std::size_t grid_height);
    std::string Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration);

private:

};

#endif