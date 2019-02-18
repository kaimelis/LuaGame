#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
class Game
{
public:

	Game();
	virtual ~Game();

	virtual void initialize();
	virtual void run();

protected:
		
	virtual void initializeWindow();
	virtual void initializeScene() = 0;
	virtual void update(float pStep);
	virtual void processEvents();
	sf::RenderWindow* window;
	float fps;

private:
	Game(const Game&);
	Game& operator=(const Game&);
};

#endif GAME_HPP
