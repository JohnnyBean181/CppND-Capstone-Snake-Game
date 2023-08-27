#include <iostream>
#include "controller.h"
#include "game.h"
#include "game2p.h"
#include "gamepvc.h"
#include "game_adv_food.h"
#include "renderer.h"
#include "menu.h"


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Menu menu;
  bool running = true;

  while (running) {
    menu.Run(controller, renderer);
    if (menu.Quit()){
      break;
    }
    switch(menu.GetSelectId()) {
      case 0: // solo game with 3 lives per game
        {
          int lives = 3;
          while (lives>0) {
            GameAdvFood game(kGridWidth, kGridHeight);
            if (game.Run(controller, renderer, kMsPerFrame) == -1) {
              std::cout << "Return to menu!\n";
              break;
            }
            std::cout << "Good game!\n";
            std::cout << "Score: " << game.GetScore() << "\n";
            std::cout << "Size: " << game.GetSize() << "\n";
            lives--;
            std::cout << lives << " lives left!\n";
          }
          break;
        }
      case 1: // pvp game with 1 life per game
        {
          Game2P game2p(kGridWidth, kGridHeight);
          
          std::string winner = game2p.Run(controller, renderer, kMsPerFrame);
          std::cout << "Winner is " << winner << "!" << std::endl;
        }
        break;
      case 2: // pvc game with 1 life per game
        {
          GamePvC game_pvc(kGridWidth, kGridHeight);
          
          std::string winner = game_pvc.Run(controller, renderer, kMsPerFrame);
          std::cout << "Winner is " << winner << "!" << std::endl;
        }
        break;
      case 3: // 
        running = false;
        break;
    }
    menu.Reset();
  }
  return 0;
}