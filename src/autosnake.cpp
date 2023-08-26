#include "autosnake.h"

void AutoSnake::Redirect(SDL_Point food) {
  // locate block
  SDL_Rect block;
  block.w = kScreenWidth / GetGridWidth();
  block.h = kScreenHeight / GetGridHeight();

  block.x = static_cast<int>(head_x) * block.w;
  block.y = static_cast<int>(head_y) * block.h;

  if (food.x != static_cast<int>(head_x)) {
    if (direction!=Direction::kLeft && direction!=Direction::kRight){
      TurnLeft();
    }
  }
  else if (food.y != static_cast<int>(head_y)) {
    if (direction!=Direction::kUp && direction!=Direction::kDown) {
      TurnLeft();
    }
  }
}

void AutoSnake::TurnLeft () {
  switch(direction) {
    case Direction::kUp: direction = Direction::kLeft; break;
    case Direction::kLeft: direction = Direction::kDown; break;
    case Direction::kDown: direction = Direction::kRight; break;
    case Direction::kRight: direction = Direction::kUp; break;
  }
}
