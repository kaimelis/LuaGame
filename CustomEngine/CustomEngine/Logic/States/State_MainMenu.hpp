#ifndef STATEMAINMENU_HPP
#define STATEMAINMENU_HPP

#include "../../Core/StateSystem/BaseState.hpp"
#include "../../Core/EventSystem/EventManager.hpp"

class State_MainMenu : public BaseState
{
public:
	State_MainMenu(StateManager* pStateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& pTime);
	void Draw();

	void MouseClick(EventDetails* pDetails);

private:
	sf::Font _font;
	sf::Text _text;

	sf::Vector2f _buttonSize;
	sf::Vector2f _buttonPos;
	unsigned int _buttonPadding;

	sf::RectangleShape _rects[3];
	sf::Text _labels[3];

};

#endif