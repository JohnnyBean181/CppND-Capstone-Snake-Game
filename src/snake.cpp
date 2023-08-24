#include "snake.h"


Snake::~Snake()
{
  //Delete particles
  /*  for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        delete particles[ i ];
    }*/
}

void Snake::Load_Particles() {
  // locate block
  SDL_Rect block;
  block.w = kScreenWidth / grid_width;
  block.h = kScreenHeight / grid_height;

  block.x = static_cast<int>(head_x) * block.w;
  block.y = static_cast<int>(head_y) * block.h;

  //Initialize particles
  for( int i = 0; i < TOTAL_PARTICLES; ++i )
  {
      particles[ i ] = std::make_unique<Particle>(block.x, block.y);
  }
}

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }

  // Update the praticles which are used for head decoration.
  if (solo) {
    UpdateParticles();
  }
}

void Snake::UpdateParticles() {
  // locate block
  SDL_Rect block;
  block.w = kScreenWidth / grid_width;
  block.h = kScreenHeight / grid_height;

  block.x = static_cast<int>(head_x) * block.w;
  block.y = static_cast<int>(head_y) * block.h;

  //Go through particles
  for( int i = 0; i < TOTAL_PARTICLES; ++i )
  {
      //Delete and replace dead particles
      if( particles[ i ]->isDead() )
      {
          // delete particles[ i ];
          // particles[ i ] = new Particle( block.x, block.y );
          std::unique_ptr<Particle> tmp_particle = std::make_unique<Particle>(block.x, block.y);
          particles[ i ].reset(tmp_particle.release());
      }
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

int Snake::GetGridWidth() {
  return grid_width;
}

int Snake::GetGridHeight() {
  return grid_height;
}

bool Snake::GetSolo() {
  return solo;
}

void Snake::SetSolo(bool is_solo) {
  solo = is_solo;
}

void Snake::SetDirection(Direction drct) {
  direction = drct;
}

void Snake::CrossDetection(Snake * snake2) {

  // Check if 2 snakes have crossed.
  int int_head_x = static_cast<int>(head_x);
  int int_head_y = static_cast<int>(head_y);

  if (snake2->SnakeCell(int_head_x, int_head_y) ) {
    alive = false;
  }
}