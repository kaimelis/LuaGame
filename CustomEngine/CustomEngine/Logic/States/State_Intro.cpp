#include "State_Intro.hpp"
#include "../../Core/StateSystem/StateManager.hpp"

State_Intro::State_Intro(StateManager* pStateManager) : BaseState(pStateManager)
{}

State_Intro::~State_Intro() {}

void State_Intro::OnCreate()
{
	_timePassed = 0.0f;

	sf::Vector2u windowSize = _stateMgr->GetContext()->_wind->GetRenderWindow()->getSize();
	_introTexture.loadFromFile("Assets/intro.png");
	_introSprite.setTexture(_introTexture);
	_introSprite.setOrigin(_introTexture.getSize().x / 2.0f,_introTexture.getSize().y / 2.0f);

	_introSprite.setPosition(windowSize.x / 2.0f, 0);

	_font.loadFromFile("Assets/arial.ttf");
	_text.setFont(_font);
	_text.setString({ "Press SPACE to continue" });
	_text.setCharacterSize(15);
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
	_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);
}

void State_Intro::OnDestroy() 
{
	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Update(const sf::Time& pTime) 
{
	if (_timePassed < 1.0f )
	{ // Less than five seconds.
		_timePassed += pTime.asSeconds();
		_introSprite.setPosition(
			_introSprite.getPosition().x,_introSprite.getPosition().y + (100 * pTime.asSeconds()));

	}
}

void State_Intro::Draw() 
{
	sf::RenderWindow* window = _stateMgr->GetContext()->_wind->GetRenderWindow();

	window->draw(_introSprite);
	if (_timePassed >= 1.0f)
	{
		window->draw(_text);
	}
}

void State_Intro::Continue(EventDetails* l_details) {
	if (_timePassed >= 1.0f) {
		_stateMgr->SwitchTo(StateType::MainMenu);
		_stateMgr->Remove(StateType::Intro);
	}
}

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}
