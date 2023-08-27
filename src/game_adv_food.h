#ifndef GAME_ADV_FOOD_H
#define GAME_ADV_FOOD_H

#include <random>
#include <memory>
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "resource.h"
#include "autosnake.h"
#include "game.h"
#include "food.h"
#include "multithreads.h"

class GameAdvFood : public Game {

public:

    GameAdvFood(std::size_t grid_width, std::size_t grid_height);
    int Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration);

    bool IsFoodAvailable();
    bool IsFoodDecayed(Uint32 current_timestamp);
    void MakeFood();
    void CleanFood();

    bool running{true};

private:
    void Update() override;
    std::unique_ptr<Food> food;
    SDL_Thread* producerThread;
    SDL_Thread* consumerThread;
    bool is_food_available;


};

#endif