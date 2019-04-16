#include "Game.hpp"

Game::Game() : _window("Lua Game", sf::Vector2u(1900,1000)), _stateManager(&_context)
{
	RestartClock();
	srand(time(nullptr));
	_context._wind = &_window;
	_context._eventManager = _window.GetEventManager();

	_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game()
{
}

Window* Game::GetWindow() 
{
	return &_window; 
}

sf::Time Game::GetElapsed()
{
	return _clock.getElapsedTime();;
}

void Game::RestartClock()
{
	_elapsed = _clock.restart();
}

void Game::Update()
{
	_window.Update();
	_stateManager.Update(_elapsed);
}

void Game::Render()
{
	_window.BeginDraw();
	//Render here
	_stateManager.Draw();
	//
	_window.EndDraw();
}

void Game::LateUpdate()
{
	_stateManager.ProcessRequests();
	RestartClock();
}
