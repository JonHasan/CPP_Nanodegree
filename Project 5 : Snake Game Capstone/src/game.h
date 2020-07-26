#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include <vector>

class Game {
 public:
 //Addition 2 Add an obstacle wall. Credit for creation of obstacle code goes to Ahmed Fathy
  Game(std::size_t grid_width, std::size_t grid_height, Obstacle &obstacle);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);


  int GetScore() const;

  int GetSize() const;

  //Acquire lives Addition 3
  int GetLives() const; 

  //Acquire High Score Addition 4
  int GetHighScore() const;  

  //Addition 4 Add public members for high_score and placeholder
  

  int high_score{place_holder};
  int place_holder = 0; 


 private:
  Snake snake;

  SDL_Point food;


  ///add private variable poison Addition 1//////
  SDL_Point poison; 
  ///////////////////////////////////////////////

  SDL_Point slowdown; 


//add variable for making obstacle walls Addition 2 
  Obstacle obstacle;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int lives{3}; 

  void PlaceFood();

  //make void function for placing poison Addition 1/////
  void PlacePoison(); 
  ///////////////////////////////////////////////////////

  //make void function for slowdown 
  void PlaceSlowDown();

  void Update();
 
};

#endif