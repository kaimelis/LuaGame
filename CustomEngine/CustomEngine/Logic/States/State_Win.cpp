#include "State_Win.hpp"
#include "../../Core/StateSystem/StateManager.hpp"

State_Win::State_Win(StateManager* pStateManager) : BaseState(pStateManager)
{}


State_Win::~State_Win() {}

void State_Win::OnCreate()
{
	_timePassed = 0.0f;

	sf::Vector2u windowSize = _stateMgr->GetContext()->_wind->GetRenderWindow()->getSize();
	_winTexture.loadFromFile("Assets/win.jpg");
	_winSprite.setTexture(_winTexture);
	_winSprite.setOrigin(_winTexture.getSize().x / 2.0f, _winTexture.getSize().y / 2.0f);

	_winSprite.setPosition(windowSize.x / 2.0f, 0);

	_font.loadFromFile("Assets/arial.ttf");
	_text.setFont(_font);
	_text.setString({ "Press SPACE to reset" });
	_text.setCharacterSize(15);
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->AddCallback(StateType::Win, "Intro_Continue", &State_Win::Reset, this);
}


void State_Win::OnDestroy()
{
	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->RemoveCallback(StateType::Win, "Intro_Continue");
}

void State_Win::Update(const sf::Time& pTime)
{
	if (_timePassed < 1.0f)
	{ // Less than five seconds.
		_timePassed += pTime.asSeconds();
		_winSprite.setPosition(
			_winSprite.getPosition().x, _winSprite.getPosition().y + (100 * pTime.asSeconds()));
	}
}

void State_Win::Draw()
{
	sf::RenderWindow* window = _stateMgr->GetContext()->_wind->GetRenderWindow();

	window->draw(_winSprite);
	if (_timePassed >= 1.0f)
	{
		window->draw(_text);
	}
}

void State_Win::Reset(EventDetails* l_details) {
	if (_timePassed >= 1.0f) {
		_stateMgr->SwitchTo(StateType::MainMenu);
		_stateMgr->Remove(StateType::Win);
	}
}

void State_Win::Activate() {}
void State_Win::Deactivate() {}

