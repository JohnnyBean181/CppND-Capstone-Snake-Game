#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include "SDL.h"
#include "particle.h"
#include "resource.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2){
          if (manual) {
            // decorate snake's head with fancy particles 
            Load_Particles();
          }
        }

  ~Snake();

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  //Flag to identify if it's robot snake.
  bool manual{true};

  //The particles
	std::unique_ptr<Particle> particles[ TOTAL_PARTICLES ];

  int GetGridWidth();
  int GetGridHeight();

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void UpdateParticles();

  // decorate snake's head with fancy particles 
  void Load_Particles();

  bool growing{false};
  int grid_width;
  int grid_height;

};

#endif