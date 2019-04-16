#ifndef GAME_HPP
#define GAME_HPP

#include "../Core/Window/Window.hpp"
#include"../Core/EventSystem/EventManager.hpp"
#include "../Core/StateSystem/StateManager.hpp"
#include "../SharedContext.hpp"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();
	Window* GetWindow();

private:
	void RestartClock();

	SharedContext _context;
	StateManager _stateManager;
	Window _window;
	sf::Clock _clock;
	sf::Time _elapsed;
};
#endif