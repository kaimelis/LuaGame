#ifndef STATEGAMEOVER_HPP
#define STATEGAMEOVER_HPP

#include "../../Core/StateSystem/BaseState.hpp"
#include "../../Core/EventSystem/EventManager.hpp"
#include "../../Core//ECS/GameObject.hpp"

class State_GameOver : public BaseState
{
public:
	State_GameOver(StateManager* pStateManager);
	~State_GameOver();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& pTime);
	void Draw();

	void Reset(EventDetails* pDetails);

private:
	sf::Texture _gameOverTexture;
	sf::Sprite _gameOverSprite;
	sf::Font _font;
	sf::Text _text;

	float _timePassed;
};


#endif