//used from repository of ahmed fathy   Github: AhmedFathy17
//Used for the wall obstacles 

#ifndef OBSTACLE_H

#define OBSTACLE_H



#include "SDL.h"

#include <vector>



class Obstacle {

     public:

          Obstacle(int grid_width, int grid_height){ this->grid_width = grid_width; this->grid_height = grid_height; placeObstacle();}

          std::vector<SDL_Point> get_obstacle();

          bool ObstacleCell(int x, int y);

   

     private:

          void placeObstacle();

          std::vector <SDL_Point> obstaclePoints;

          size_t grid_width;

          size_t grid_height;

};

#endif