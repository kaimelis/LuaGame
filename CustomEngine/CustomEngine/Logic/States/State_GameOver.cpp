#include "State_GameOver.hpp"
#include "../../Core/StateSystem/StateManager.hpp"

State_GameOver::State_GameOver(StateManager* pStateManager) : BaseState(pStateManager)
{}


State_GameOver::~State_GameOver() {}

void State_GameOver::OnCreate()
{
	_timePassed = 0.0f;

	sf::Vector2u windowSize = _stateMgr->GetContext()->_wind->GetRenderWindow()->getSize();
	_gameOverTexture.loadFromFile("Assets/gameover.jpg");
	_gameOverSprite.setTexture(_gameOverTexture);
	_gameOverSprite.setOrigin(_gameOverTexture.getSize().x / 2.0f, _gameOverTexture.getSize().y / 2.0f);

	_gameOverSprite.setPosition(windowSize.x / 2.0f, 0);

	_font.loadFromFile("Assets/arial.ttf");
	_text.setFont(_font);
	_text.setString({ "Press SPACE to reset" });
	_text.setCharacterSize(15);
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->AddCallback(StateType::GameOver, "Intro_Continue", &State_GameOver::Reset, this);
}


void State_GameOver::OnDestroy()
{
	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->RemoveCallback(StateType::GameOver, "Intro_Continue");
}

void State_GameOver::Update(const sf::Time& pTime)
{
	if (_timePassed < 2.0f)
	{ // Less than five seconds.
		_timePassed += pTime.asSeconds();
		_gameOverSprite.setPosition(
			_gameOverSprite.getPosition().x, _gameOverSprite.getPosition().y + (150 * pTime.asSeconds()));
	}
}

void State_GameOver::Draw()
{
	sf::RenderWindow* window = _stateMgr->GetContext()->_wind->GetRenderWindow();

	window->draw(_gameOverSprite);
	if (_timePassed >= 1.0f)
	{
		window->draw(_text);
	}
}

void State_GameOver::Reset(EventDetails* l_details) {
	if (_timePassed >= 1.0f) {
		_stateMgr->SwitchTo(StateType::MainMenu);
		_stateMgr->Remove(StateType::GameOver);
	}
}

void State_GameOver::Activate() {}
void State_GameOver::Deactivate() {}

