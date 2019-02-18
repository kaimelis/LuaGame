#include <iostream>
#include "Game.hpp"

Game::Game(): window(NULL), fps(0)
{}

Game::~Game()
{
	delete window;
}

void Game::initialize()
{
	initializeWindow();
	initializeScene();

}

void Game::initializeWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game!", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
}

void Game::run()
{
	sf::Clock renderClock;
	int frameCount = 0;
	float timeSinceLastFPSCalculation = 0;

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window->isOpen())
	{
		timeSinceLastUpdate += updateClock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			while (timeSinceLastUpdate > timePerFrame) {
				timeSinceLastUpdate -= timePerFrame;
				update(timePerFrame.asSeconds());
			}

			window->display();
			frameCount++;
			timeSinceLastFPSCalculation += renderClock.restart().asSeconds();

			if (timeSinceLastFPSCalculation > 1) {
				fps = frameCount / timeSinceLastFPSCalculation;
				timeSinceLastFPSCalculation -= 1;
				frameCount = 0;
			}
		}
		processEvents();
	}
}

void Game::update(float pStep)
{
}

void Game::processEvents()
{
	sf::Event event;
	bool exit = false;

	while (window->pollEvent(event)) 
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				exit = true;
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					exit = true;
				}
				break;
			case sf::Event::Resized:
				break;

			default:
				break;
		}
	}

	if (exit) 
	{
		window->close();
	}
}
