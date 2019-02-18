#ifndef MAINGAME_HPP
#define MAINGAME_HPP

#include "Game.hpp"

class MainGame : public Game
{
public :
	MainGame();
	~MainGame();
	virtual void initialize();
protected:
	virtual void initializeScene();
private:
	MainGame(const MainGame&);
	MainGame& operator=(const MainGame&);
};

#endif MAINGAME_HPP