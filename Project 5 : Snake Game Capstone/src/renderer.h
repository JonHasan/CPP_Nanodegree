#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "obstacle.h"

class Renderer {
 public:
 // need to a reference to obstacle. Obstacle addition was taken from Ahmed Fathy Addition 2 
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, Obstacle &obstacle);
  ~Renderer();

//Add poison and slowdown variables  Addition 1 and 6

  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &poison, SDL_Point const &slowdown);
  
  //Add lives counter to update window title Addition 3 Add high_score to update window title Addition 4
  void UpdateWindowTitle(int score, int fps, int lives, int high_score);




 private:
  SDL_Window *sdl_window;;
  SDL_Renderer *sdl_renderer;

  //Creation of obstacle object with obstacle.h and obstacle.cpp. Addition 2 
  Obstacle obstacle; 

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

};

#endif