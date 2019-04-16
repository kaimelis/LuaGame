#ifndef STATEPAUSED_HPP
#define STATEPAUSED_HPP

#include "../../Core/StateSystem/BaseState.hpp"
#include "../../Core/EventSystem/EventManager.hpp"

class State_Paused : public BaseState
{
public:
	State_Paused(StateManager* pStateManager);
	~State_Paused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& pTime);
	void Draw();

	void Unpause(EventDetails* pDetails);

private:
	sf::Font _font;
	sf::Text _text;
	sf::RectangleShape _rect;

};

#endif