#ifndef SHAREDCONTEX_HPP
#define SHAREDCONTEX_HPP

#include "Core/Window/Window.hpp"
#include"Core//EventSystem/EventManager.hpp"

struct SharedContext
{
	SharedContext():_wind(nullptr),_eventManager(nullptr) {}
	Window* _wind;
	EventManager* _eventManager;
};

#endif