#include "Logic/Game.hpp"

int main(int argc, void** argv[])
{
	Game game;
	while (!game.GetWindow()->isDone())
	{
		game.Update();
		game.Render();
		game.LateUpdate();
	}
	return 0;
}