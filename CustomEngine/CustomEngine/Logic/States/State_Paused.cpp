#include "State_Paused.hpp"
#include "../../Core/StateSystem/StateManager.hpp"

State_Paused::State_Paused(StateManager* pStateManager): BaseState(pStateManager) {}

State_Paused::~State_Paused() {}

void State_Paused::OnCreate() 
{
	SetTransparent(true); // Set our transparency flag.
	_font.loadFromFile("Assets/arial.ttf");
	_text.setFont(_font);
	_text.setString(sf::String("PAUSED"));
	_text.setCharacterSize(14);
	_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = _stateMgr->GetContext()->_wind->GetRenderWindow()->getSize();

	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
	_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	_rect.setSize(sf::Vector2f(windowSize));
	_rect.setPosition(0, 0);
	_rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->AddCallback(StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() 
{
	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Draw() 
{
	sf::RenderWindow* wind = _stateMgr->GetContext()->_wind->GetRenderWindow();
	wind->draw(_rect);
	wind->draw(_text);
}

void State_Paused::Unpause(EventDetails* l_details)
{
	_stateMgr->SwitchTo(StateType::Game);
}

void State_Paused::Activate() {}
void State_Paused::Deactivate() {}
void State_Paused::Update(const sf::Time& l_time) {}