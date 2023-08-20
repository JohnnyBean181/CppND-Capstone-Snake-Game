#include "autosnake.h"

void AutoSnake::Redirect() {
  // locate block
  SDL_Rect block;
  block.w = kScreenWidth / GetGridWidth();
  block.h = kScreenHeight / GetGridHeight();

  block.x = static_cast<int>(head_x) * block.w;
  block.y = static_cast<int>(head_y) * block.h;

  // if the snake is close to the board.
  if (block.y < kScreenHeight/10*9 && block.x < kScreenWidth/10) {
    if (direction!=Direction::kDown) {
      TurnLeft();
    }
    return;
  }
  if (block.y > kScreenHeight/10*9 && block.x < kScreenWidth/10*9) {
    if (direction!=Direction::kRight) {
      TurnLeft();
    }
    return;
  }
  if (block.y > kScreenHeight/10 && block.x > kScreenWidth/10*9) {
    if (direction!=Direction::kUp) {
      TurnLeft();
    }
    return;
  }
  if (block.y < kScreenHeight/10 && block.x > kScreenWidth/10) {
    if (direction!=Direction::kLeft) {
      TurnLeft();
    }
    return;
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
