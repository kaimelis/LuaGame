#include "Core/Game.hpp"
#include "Core/MainGame.hpp"

int main()
{
	Game* game = new MainGame();
	game->initialize();
	game->run();
	
	delete game;
	return 0;
}