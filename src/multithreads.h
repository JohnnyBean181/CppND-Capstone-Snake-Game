#ifndef MULTITHREAD_H
#define MULTITHREAD_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"
#include "food.h"
#include "resource.h"


class GameAdvFood;

// The protective mutex
extern SDL_mutex* gBufferLock;

// The conditions
extern SDL_cond* gCanProduce;
extern SDL_cond* gCanEat;
extern SDL_cond* gCanThrow;

int Producer( void* data );
int Consumer( void* data );
void Produce(GameAdvFood* game);
void Consume(GameAdvFood* game);

#endif