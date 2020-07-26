#include "game.h"
#include <iostream>
#include "SDL.h"

//Add obstacle argument Taken from Ahmed Fathy Addition 2
Game::Game(std::size_t grid_width, std::size_t grid_height, Obstacle &obstacle)
    : snake(grid_width, grid_height, obstacle),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      obstacle(obstacle) {PlaceFood(), PlacePoison(), PlaceSlowDown(); }

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();

    //add poison Addition 1 Add slowdown Addition 6 
    renderer.Render(snake, food, poison, slowdown);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, lives, high_score);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}



void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }

    //checks if food is not on the obstacle. Taken from Ahmed Fathy 
    if (!obstacle.ObstacleCell(x, y)) {

      food.x = x;

      food.y = y;

      return;

    }

  }
}

////Add void function for placing poison in game: Addition 1 ////////
void Game::PlacePoison() {
  int x, y;
  while(true) {
    x = random_w(engine);
    y = random_h(engine);
    //check if snake isn't there and if food isnt there
    if(!snake.SnakeCell(x,y) && food.x != x && food.y != y){
      poison.x = x;
      poison.y = y;
      return; 
    }
    if (!obstacle.ObstacleCell(x, y)) {

      poison.x = x;

      poison.y = y;

      return;

    }
  }
}
////////////////////////////////////////////////////////////////////

////////////////////Add void function to place slow down pellet: Addition 6////
void Game::PlaceSlowDown(){
  int x,y;
  while(true) {
    x = random_w(engine);
    y = random_h(engine);
    //check if snake and if food and if poison isnt there
    if(!snake.SnakeCell(x,y) && food.x!= x && food.y != y && poison.x!=x && poison.y != y){
      slowdown.x = x;
      slowdown.y = y; 
    }
    if (!obstacle.ObstacleCell(x, y)) {

      slowdown.x = x;

      slowdown.y = y;

      return;

    }

  }
}
 
//Game Update method for single player game  
void Game::Update() {
  if (!snake.alive) {place_holder = high_score;  return;}

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    if(score > high_score){
      high_score = score; 
    } 

    PlaceFood();

    
    PlacePoison(); 
    
    PlaceSlowDown();


    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Did snake eat bad food? Addition 1 
  if (poison.x == new_x && poison.y == new_y){
    lives--;

    if(lives == 0){
      snake.alive = false; 
    } else{

    PlaceFood();

    PlacePoison();

    PlaceSlowDown();

    }
    
  }

  if (slowdown.x == new_x && slowdown.y == new_y){
    snake.speed -= .02;

    PlaceFood();

    PlacePoison();
    
    PlaceSlowDown();
  }

  for (auto const &item: obstacle.get_obstacle()){
    if ( item.x == new_x && item.y == new_y){
      lives--;
      if(lives == 0){
        snake.alive = false;
      } 
    }
  }

}


int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
//Add a feature for lives Addition 3 
int Game::GetLives() const {return lives;}
//Add a feature for high score and acquiring list of high_scores Addition 4; 
int Game::GetHighScore() const{return high_score;}






