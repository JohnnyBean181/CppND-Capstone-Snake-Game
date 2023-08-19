#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "particle.h"
#include "snake.h"
#include "resource.h"

//Scene textures
extern LTexture gRedTexture;
extern LTexture gGreenTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

extern SDL_Renderer *sdl_renderer;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake& snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  // set sdl_renderer as global variable.
  //SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif