#include "gamepvc.h"

GamePvC::GamePvC(std::size_t grid_width, std::size_t grid_height)
    : Game(grid_width, grid_height),
    _snake_robot(std::make_unique<AutoSnake>(grid_width, grid_height)){
    _snake->SetSolo(false);
    _snake_robot->SetSolo(false);

}

std::string GamePvC::Run(Controller const &controller, Renderer &renderer,
    std::size_t target_frame_duration){
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _snake.get());
    _snake_robot->Redirect(food); // AI control for robot snake
    Update();
    renderer.Render(_snake.get(), _snake_robot.get(), food);

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

    if (!_snake->alive or !_snake_robot->alive) {
      running = false;
      SDL_Delay(2000); // pause 2 seconds before leaving
    }
  }
  // return who is the winner
  if (GetScore() > GetScore2()) {
    return "Player";
  } else 
  if (GetScore() < GetScore2()){
    return "Computer";
  } else {
    return "Nobody";
  }
}

void GamePvC::Update() {
  if (!_snake->alive || !_snake_robot->alive) return;

  _snake->Update();
  // also update robot snake
  _snake_robot->Update();
  // scan snake 1
  int new_x = static_cast<int>(_snake->head_x);
  int new_y = static_cast<int>(_snake->head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    _snake->GrowBody();
    _snake->speed += 0.02;
  }
  // scan snake 2
  int new_x_2 = static_cast<int>(_snake_robot->head_x);
  int new_y_2 = static_cast<int>(_snake_robot->head_y);

  // Check if there's food over here
  if (food.x == new_x_2 && food.y == new_y_2) {
    score2++;
    PlaceFood();
    // Grow snake and increase speed.
    _snake_robot->GrowBody();
    _snake_robot->speed += 0.02;
  }
  // check if 2 snakes cross.
  _snake->CrossDetection(_snake_robot.get());
  _snake_robot->CrossDetection(_snake.get());
}
// return score for snake 2
int GamePvC::GetScore2() const { return score2; }