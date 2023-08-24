#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <iostream>
#include "SDL2/SDL.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake *snake) const;
  void HandleMenuInput(bool &running, bool &quit, int &menu_selected, int &menu_last_selected) const;
  void Handle2PInput(bool &running, Snake *snake1, Snake *snake2) const;

 private:
  void ChangeDirection(Snake *snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif