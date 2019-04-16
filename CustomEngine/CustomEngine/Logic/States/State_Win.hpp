#ifndef STATEWIN_HPP
#define STATEWIN_HPP

#include "../../Core/StateSystem/BaseState.hpp"
#include "../../Core/EventSystem/EventManager.hpp"
#include "../../Core//ECS/GameObject.hpp"

class State_Win : public BaseState
{
public:
	State_Win(StateManager* pStateManager);
	~State_Win();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& pTime);
	void Draw();

	void Reset(EventDetails* pDetails);

private:
	sf::Texture _winTexture;
	sf::Sprite _winSprite;
	sf::Font _font;
	sf::Text _text;

	float _timePassed;
};


#endif#pragma once
