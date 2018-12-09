#include "../Headers/Game.h"
#include "../Headers/Input.h"
#include "../Headers/Arena.h"

int main(int argc, char* argv[]) 
{
	Game* game = new Game();	//create a new Game object

	while (game && game->GameRunning())
	{

			game->Update(); //update the game
		
	}

		delete game;
		game = nullptr;
	
	return 0;						//exit nicely. 

}