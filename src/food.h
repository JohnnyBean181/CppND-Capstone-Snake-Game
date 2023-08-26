#ifndef FOOD_H
#define FOOD_H

#include <memory>
#include <iostream>
#include "SDL2/SDL.h"

class Food { 
  public:
    enum class FoodType { normal, poisonous };

    Food (int x, int y);

    SDL_Point* GetPosition();
    Uint32 GetTimeStamp();

    bool IsPoisonous();
    int GetDecayTime();

  private:
    std::unique_ptr<SDL_Point> position;
    FoodType type;
    Uint32 start_timestamp = SDL_GetTicks();
    int time_to_decay;
};

#endif