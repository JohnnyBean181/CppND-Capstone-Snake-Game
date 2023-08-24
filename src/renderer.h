#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "particle.h"
#include "snake.h"
#include "resource.h"
#include "autosnake.h"

//Scene textures
extern LTexture gRedTexture;
extern LTexture gGreenTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

extern LTexture gTextTexture_1p;
extern LTexture gTextTexture_2p;
extern LTexture gTextTexture_pvc;
extern LTexture gTextTexture_exit;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake* snake, SDL_Point const &food);
  void RenderMainMenu(int &menu_selected, int &menu_last_selected);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font* gFont;
  bool LoadImage();
  void UnloadImage();
  void DrawText(int id, int flag);

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif