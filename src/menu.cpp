#include "menu.h"

Menu::Menu() {};

int Menu::Run(Controller const &controller, Renderer &renderer) {

  bool running = true;
  int selected = 0;

  while (running) {

    // Input, Render - the main menu loop.
    controller.HandleMenuInput(running, quit, menu_selected, menu_last_selected);
    selected = menu_selected;
    renderer.RenderMainMenu(menu_selected, menu_last_selected);
    SDL_Delay(100);
  }
  return selected;
}

int Menu::GetSelectId() {
    return menu_selected;
}

void Menu::Reset() {
    menu_last_selected = menu_selected;
    menu_selected = 0;
}

bool Menu::Quit() {
    return quit;
}