#ifndef STATEINTRO_HPP
#define STATEINTRO_HPP

#include "../../Core/StateSystem/BaseState.hpp"
#include "../../Core/EventSystem/EventManager.hpp"

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager* pStateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& pTime);
	void Draw();

	void Continue(EventDetails* pDetails);

private:
	sf::Texture _introTexture;
	sf::Sprite _introSprite;
	sf::Font _font;
	sf::Text _text;

	float _timePassed;
};

#endif