#include "game_adv_food.h"

GameAdvFood::GameAdvFood(std::size_t grid_width, std::size_t grid_height)
    : Game(grid_width, grid_height),
    is_food_available(false){
    producerThread = SDL_CreateThread( Producer, "Producer", this );
    consumerThread = SDL_CreateThread( Consumer, "Consumer", this );
}

int GameAdvFood::Run(Controller const &controller, Renderer &renderer,
    std::size_t target_frame_duration){
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool force_break = false;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _snake.get());
    Update();
    renderer.Render(_snake.get(), food.get());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    // if user quit
    if (!running ) {
      //Signal producer to help it stop
	    SDL_CondSignal( gCanProduce );
      force_break = true;
    }

    // if snake is not alive
    if (!_snake->alive ) {
      running = false;
      SDL_Delay(2000); // pause for 2 sec before leaving
      //Signal producer to help it stop
	    SDL_CondSignal( gCanProduce );
    }
  }

  //Wait for producer and consumer to finish
  SDL_WaitThread( consumerThread, NULL );
  SDL_WaitThread( producerThread, NULL );
  
  if (force_break) {
    return -1;
  }

  return 0;
}

void GameAdvFood::Update() {
  if (!_snake->alive ) return;

  _snake->Update();
  
  int new_x = static_cast<int>(_snake->head_x);
  int new_y = static_cast<int>(_snake->head_y);

  //Lock
  SDL_LockMutex( gBufferLock );
  // std::cout << "food available" << IsFoodAvailable() << std::endl;
  // Check if there's food over here
  if( !IsFoodAvailable() ) {
    SDL_CondWait( gCanEat, gBufferLock );
  }
  // std::cout << food->GetPosition() << std::endl; 
  if (food->GetPosition()->x == new_x && food->GetPosition()->y == new_y) {
    score++;

    CleanFood();
    //Signal producer
    SDL_CondSignal( gCanProduce );
    // reverse the snake if poisonous food is eaten
    if (food->IsPoisonous()) {
        _snake->Reverse();
    }

    // Grow snake and increase speed.
    _snake->GrowBody();
    _snake->speed += 0.02;
  }

  //Unlock
  SDL_UnlockMutex( gBufferLock );

}

bool GameAdvFood::IsFoodAvailable() {
    return is_food_available;
}

void GameAdvFood::MakeFood() {
  // initialize or refresh Food object.
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake->SnakeCell(x, y)) {
      food = std::make_unique<Food>(x, y); // by assigning new value, old food will be recycled by C++
      is_food_available = true;
      return;
    }
  }
}
// return if the food should be refreshed.
bool GameAdvFood::IsFoodDecayed(Uint32 current_timestamp) {
    Uint32 time_gap = current_timestamp - food->GetTimeStamp();

    if ( time_gap > food->GetDecayTime()*1000) {
        return true;
    }
    
    return false;
}
// set the food as unavailable, especially after food is eaten or decayed.
void GameAdvFood::CleanFood() {
    is_food_available = false;
}