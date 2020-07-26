//used from repository of ahmed fathy   Github: AhmedFathy17

//This is for addition 2 which is the wall obstacles


#include "obstacle.h"

#include <iostream>

#include "SDL.h"


//create the obstacles using a for loop for each one
void Obstacle::placeObstacle(){



    SDL_Point point;




    //creates a horizontal green wall 

    for(int i=0; i<grid_width/2; i++)

    {

        point.x = i + (grid_width/4);

        point.y = grid_height/3;

        obstaclePoints.push_back(point);

    }

    //create a vertical wall
    for(int i=0; i<grid_width/2; i++)

    {

        point.x = (grid_width/3);

        point.y = i + (grid_height/4);

        obstaclePoints.push_back(point);

    }


    //create another horizontal green wall
    for(int i=0; i<grid_width/2; i++)

    {

        point.x = i + (grid_width/4);

        point.y = 2*(grid_height/3);

        obstaclePoints.push_back(point);

    }

     



}


//getter function for obstaclePoints
std::vector<SDL_Point> Obstacle:: get_obstacle(){

     return obstaclePoints;

 }


//use the newly acquired obstacle points to determine if the obstacle is in x,y coordinates specified
 bool Obstacle::ObstacleCell(int x, int y)

{

  for (auto const &item : obstaclePoints)

  {

    if (x == item.x && y == item.y)

    {

      return true;

    }

  }

  return false;

}