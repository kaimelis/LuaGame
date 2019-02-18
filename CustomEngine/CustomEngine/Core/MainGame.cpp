#include "MainGame.hpp"

MainGame::MainGame() : Game()
{

}

void MainGame::initialize()
{
	Game::initialize();


}

void MainGame::initializeScene() 
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

}


MainGame::~MainGame()
{}