#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "obstack.h"
#include "obstacle.h"

using std::cout; 
using std::cin;

int main() {


  //Additon 5: Adding a start screen. Use switch statement to activate game or other options. This code was taken from a Cplusplus.com post from poster called BlitzCoder
    
  int choice;
  bool gameOn = true;
  while (gameOn != false){
   

  
  
    cout << "**************Welcome to Snake Game!*****************\n";

    cout << "\n" << "   C++ Nanodegree Capstone Project " << "\n";
    cout << "\n" << "     Made by Jonathan Hasan       " << "\n";
    cout << "\n" << "----------------------------" << "\n";
    
    cout << " 1 - Start the game.\n";
    cout << " 2 - The story.\n";
    cout << " 3 - Need Help?.\n";
    cout << " 4 - Exit.\n";
    cout << " Enter your choice and press return: ";

    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      
    cout <<"\n";
    cout << "game start!\n";

    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    Obstacle obstacle(kGridWidth, kGridHeight);
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, obstacle);
    Controller controller;
    Game game(kGridWidth, kGridHeight, obstacle);
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
    std::cout << "High_Score: " << game.GetHighScore() << "\n";
    cout <<"\n";
    break;
  }

  case 2:
    cout <<"\n";
    cout << "Story so far....\n";
    cout << "This is Snake Game.... That is all.... Good Luck \n";
    cout <<"\n";
    break;

  case 3:
    cout <<"\n";
    cout << "Ahahah, you really think I will help you?\n";
    cout << "Don't worry, I will! Get the yellow pellets and avoid the red poison and green wall. Green wall is instant death. The purple pellet will help later in the game. That Simple! \n";
    cout << "Good bye! ";
    cout <<"\n";
    break;

  case 4:
    cout <<"\n";
    cout << "End of Program. See you next time. Thanks for playing!\n";
    gameOn = false;
    cout <<"\n";
    break;

  default:
    cout <<"\n";
    cout << "Not a Valid Choice. \n";
    cout << "Choose again.\n";
    cin >> choice;
    cout <<"\n";
    break;
    }

  }
  return 0; 
}