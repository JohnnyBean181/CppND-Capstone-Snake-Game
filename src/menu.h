#ifndef MENU_H
#define MENU_H

#include <random>
#include <memory>
#include <iostream>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "resource.h"
#include "autosnake.h"

class Menu {
 public:
  Menu();

  int Run(Controller const &controller, Renderer &renderer);
  int GetSelectId();
  void Reset();
  bool Quit();

 private:

  int menu_selected{0};
  int menu_last_selected{-1};
  bool quit{false};
};

#endif