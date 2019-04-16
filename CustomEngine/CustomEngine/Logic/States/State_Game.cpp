#include "State_Game.hpp"
#include "../../Core/StateSystem/StateManager.hpp"
#include <experimental/filesystem>
#include <stdlib.h> 

namespace fs = std::experimental::filesystem;

std::vector<GameObject*>* State_Game::_gameObjects = new std::vector<GameObject*>();
State_Game::State_Game(StateManager* pStateManager): BaseState(pStateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate()
{
	
	_timePassed = 0.0f;
	initialiseLua();
	initialiseHUD();

	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	evMgr->AddCallback(StateType::Game, "Mouse_Left", &State_Game::MouseClick, this);

	if (_gameObjects->size() > 0)
	{
		for (int i = 0; i < _gameObjects->size(); i++)
		{
			_gameObjects->at(i)->SetPosition(sf::Vector2f(i * (_gameObjects->at(i)->GetSprite().getPosition().x + 300), _stateMgr->GetContext()->_wind->GetWindowSize().y / 2 + 70));
			//std::cout << _gameObjects->at(i)->GetPosition().x << " x; " << _gameObjects->at(i)->GetPosition().y << " y;" << std::endl;
			_gameObjects->at(i)->SetTextPosition();
		}
	}

}

void State_Game::OnDestroy()
{
	EventManager* evMgr = _stateMgr->GetContext()->_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Key_P");
	evMgr->RemoveCallback(StateType::Game, "Mouse_Left");
	lua_close(_state);
}

void State_Game::Update(const sf::Time& pTime) 
{
	/*
	sf::Vector2u l_windSize = _stateMgr->GetContext()->_wind->GetWindowSize();
	sf::Vector2u l_textSize = _texture.getSize();

	if ((_sprite.getPosition().x > l_windSize.x - l_textSize.x && _increment.x > 0) ||
		(_sprite.getPosition().x < 0 && _increment.x < 0))
	{
		_increment.x = -_increment.x;
	}

	if ((_sprite.getPosition().y > l_windSize.y - l_textSize.y && _increment.y > 0) ||
		(_sprite.getPosition().y < 0 && _increment.y < 0))
	{
		_increment.y = -_increment.y;
	}

	_sprite.setPosition(_sprite.getPosition().x + (_increment.x * pTime.asSeconds()),
		_sprite.getPosition().y + (_increment.y * pTime.asSeconds()));
		*/
	//updateLua();

	if (_timePassed < 1.0f && _activateTimer)
	{ // Less than five seconds.
		_timePassed += pTime.asSeconds();
		if (_timePassed > 1.0f)
		{
			debugText.setString("PLAYER TURN");
			UpdateHUDInformation();
			playerMana += 1;
			playerTurn = true;
			_timePassed = 0;
			_activateTimer = false;
		}
	}
}

void State_Game::Draw() 
{
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_background);
	if (_gameObjects->size() > 0 )
	{
		for (int i = 0; i < _gameObjects->size(); i++)
		{
			if (i <= 4)
			{
				_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_gameObjects->at(i)->GetSprite());
				_cardsInHand += 1;
				_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_gameObjects->at(i)->GetDamageText());
				_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_gameObjects->at(i)->GetHealthText());
				_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_gameObjects->at(i)->GetNameText());
				_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_gameObjects->at(i)->GetDescriptionText());
				_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_gameObjects->at(i)->GetManaText());
				_gameObjects->at(i)->SetIsOnBoard(true);
				isCardHandFull = false;
			}
		}
	}

#pragma region DrawingHUD
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_rects);
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_buttonText);
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_playerHealth);
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_playerMana);
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(_enemyHealth);
	_stateMgr->GetContext()->_wind->GetRenderWindow()->draw(debugText);

#pragma endregion	
}

void State_Game::MainMenu(EventDetails* pDetails) 
{
	_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* pDetails) {
	_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate() {}

void State_Game::Deactivate() {}

#pragma region UI
void State_Game::initialiseHUD()
{
	_font.loadFromFile("Assets/arial.ttf");

	_bakgroundTexture.loadFromFile("Assets/background.png");
	_background.setTexture(_bakgroundTexture);

#pragma region ButtonNextTurn
	_buttonSize = sf::Vector2f(200.0f, 120.0f);
	_buttonPos = sf::Vector2f(_stateMgr->GetContext()->_wind->GetWindowSize().x / 2 + 800, _stateMgr->GetContext()->_wind->GetWindowSize().y / 2 - 300);
	_buttonPadding = 4; // 4px.

	std::string str = "NEXT TURN";

	sf::Vector2f buttonPosition(_buttonPos.x, _buttonPos.y + (_buttonSize.y + _buttonPadding));
	_rects.setSize(_buttonSize);
	_rects.setFillColor(sf::Color::Black);

	_rects.setOrigin(_buttonSize.x / 2.0f, _buttonSize.y / 2.0f);
	_rects.setPosition(buttonPosition);

	_buttonText.setStyle(sf::Text::Bold);
	_buttonText.setFont(_font);
	_buttonText.setString(sf::String(str));
	_buttonText.setCharacterSize(30);
	_buttonText.setFillColor(sf::Color::White);

	sf::FloatRect rect = _buttonText.getLocalBounds();
	_buttonText.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	_buttonText.setPosition(buttonPosition);
#pragma endregion

#pragma region PlayerHealthHUD
	_playerHealth.setFont(_font);
	_playerHealth.setFillColor(sf::Color::Red);
	std::stringstream ss;
	ss << playerHealth;
	_playerHealth.setString(ss.str());
	_playerHealth.setStyle(sf::Text::Bold);
	_playerHealth.setCharacterSize(70);
	sf::FloatRect textRect = _playerHealth.getLocalBounds();
	_playerHealth.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_playerHealth.setPosition(_stateMgr->GetContext()->_wind->GetWindowSize().x - 200, _stateMgr->GetContext()->_wind->GetWindowSize().y - 290);
#pragma endregion

#pragma region PlayerManaHUD
	_playerMana.setFont(_font);
	_playerMana.setFillColor(sf::Color::White);
	_playerMana.setStyle(sf::Text::Bold);
	_playerMana.setString(std::to_string(playerMana));
	_playerMana.setCharacterSize(70);
	sf::FloatRect textRect2 = _playerMana.getLocalBounds();
	_playerMana.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
	_playerMana.setPosition(_stateMgr->GetContext()->_wind->GetWindowSize().x - 200, _stateMgr->GetContext()->_wind->GetWindowSize().y - 110);
#pragma endregion

#pragma region EnemyHealth
	_enemyHealth.setFont(_font);
	_enemyHealth.setFillColor(sf::Color::Red);
	_enemyHealth.setString(std::to_string(enemyHealth));
	_enemyHealth.setStyle(sf::Text::Bold);
	_enemyHealth.setCharacterSize(50);
	sf::FloatRect textRect3 = _enemyHealth.getLocalBounds();
	_enemyHealth.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
	_enemyHealth.setPosition(_stateMgr->GetContext()->_wind->GetWindowSize().x / 12 + 50, _stateMgr->GetContext()->_wind->GetWindowSize().y / 12 + 40);
#pragma endregion

#pragma region DebugText

	debugText.setFont(_font);
	debugText.setFillColor(sf::Color::Green);
	debugText.setCharacterSize(50);
	sf::FloatRect textRect4 = debugText.getLocalBounds();
	debugText.setOrigin(textRect4.left + textRect4.width / 2.0f, textRect4.top + textRect4.height / 2.0f);
	debugText.setPosition(_stateMgr->GetContext()->_wind->GetWindowSize().x / 2 - 100, _stateMgr->GetContext()->_wind->GetWindowSize().y / 12);

	debugText.setString("PLAYER TURN");

#pragma endregion

#pragma region CARDS INFO
	if (_gameObjects->size() > 0)
	{
		for (int i = 0; i < _gameObjects->size(); i++)
		{
			_gameObjects->at(i)->_damageText.setFont(_font);
			_gameObjects->at(i)->_healthText.setFont(_font);
			_gameObjects->at(i)->_manaText.setFont(_font);
			_gameObjects->at(i)->_nameText.setFont(_font);
			_gameObjects->at(i)->_descriptionText.setFont(_font);
		}
	}
#pragma endregion


}

void State_Game::MouseClick(EventDetails* l_details)
{
	sf::Vector2f oldPosition;
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = _buttonSize.x / 2.0f;
	float halfY = _buttonSize.y / 2.0f;

	if (mousePos.x >= _rects.getPosition().x - halfX &&
		mousePos.x <= _rects.getPosition().x + halfX &&
		mousePos.y >= _rects.getPosition().y - halfY &&
		mousePos.y <= _rects.getPosition().y + halfY && playerTurn)
	{
		//_stateMgr->SwitchTo(StateType::Game);
		std::cout << "Next Turn" << std::endl;
		playerTurn = false;
		EnemyTurn();

	}

	//TODO  : make it nicer
	if (playerTurn && playerMana > 0)
	{
		if (_gameObjects->size() > 0)
		{
			for (int i = 0; i < _gameObjects->size(); i++)
			{
				if (mousePos.x > _gameObjects->at(i)->GetPosition().x &&
					(mousePos.x < _gameObjects->at(i)->GetPosition().x + _gameObjects->at(i)->GetSprite().getTextureRect().width) &&
					mousePos.y > _gameObjects->at(i)->GetPosition().y &&
					(mousePos.y < _gameObjects->at(i)->GetPosition().y + _gameObjects->at(i)->GetSprite().getTextureRect().height) &&
					_gameObjects->at(i)->GetMana() <= playerMana)
				{
					if (_gameObjects->at(i)->GetHealth() > 0)
					{
						enemyHealth -= _gameObjects->at(i)->GetDamage();
						if (enemyHealth <= 0)
						{
							_stateMgr->SwitchTo(StateType::Win);
						}
					}
					else
					{
						OnEnableCard();
					}
					playerMana -= _gameObjects->at(i)->GetMana();
					UpdateHUDInformation();
					playerTurn = false;
					EnemyTurn();

				}
			}
		}
	}

}

void State_Game::UpdateHUDInformation()
{
	std::stringstream ss;
	ss << playerHealth;
	_playerHealth.setString(ss.str());

	std::stringstream se;
	se << enemyHealth;
	_enemyHealth.setString(se.str());

	_playerMana.setString(std::to_string(playerMana));
}
#pragma endregion

#pragma region LOGIC
void State_Game::CheckCards(std::string pName)
{
	//go through all cards
	//check which ones have 0 health
	//then destroy them
	sf::Vector2f oldPosition;
	for (size_t i = 0; i < _gameObjects->size(); i++)
	{
		if (_gameObjects->at(i)->GetName() == pName && _gameObjects->at(i)->GetHealth() <= 0)
		{
			oldPosition = _gameObjects->at(i)->GetPosition();
			OnDisableCard();
			_gameObjects->at(i)->DestroyCard();
			_gameObjects->erase(_gameObjects->begin() + i);

		}
		if (i == 4)
		{
			_gameObjects->at(i)->SetIsOnBoard(true);
			_gameObjects->at(i)->SetPosition(oldPosition);
			_gameObjects->at(i)->SetTextPosition();
		}

	}
}

void State_Game::EnemyTurn()
{
	_activateTimer = true;
	debugText.setString("ENEMY TURN");
	int random = rand() % 10 + 1;
	std::cout << std::to_string(random)  << "Random number"<< std::endl;
	if (random <= 5)
	{
		int random2 = rand() & 4;
		std::cout << std::to_string(random2) << "Random index" <<std::endl;
		std::cout << _gameObjects->at(random2)->GetName() << std::endl;

		if (_gameObjects->at(random2)->GetHealth() > 0)
		{
			_gameObjects->at(random2)->MakeDamage(enemyDamage);
			CheckCards(_gameObjects->at(random2)->GetName());
		}
		else
		{
			playerHealth -= enemyDamage;
			if (playerHealth <= 0)
				_stateMgr->SwitchTo(StateType::GameOver);
		}
	}
	else
	{
		playerHealth -= enemyDamage;
		if(playerHealth <= 0 )
			_stateMgr->SwitchTo(StateType::GameOver);
	}
	std::cout << "Enemy turn ended" << std::endl;

}

GameObject* State_Game::GetGameObject(std::string pName)
{
	for (int i = 0; i < _gameObjects->size(); i++)
	{
		if (_gameObjects->at(i)->GetName() == pName)
		{
			return _gameObjects->at(i);
		}
	}
}
#pragma endregion

#pragma region LUA

void State_Game::initialiseLua()
{
	_state = luaL_newstate();
	luaL_openlibs(_state); /* Load Lua libraries */
	registerFunctions();
	registerCards();

}

void State_Game::registerCards()
{
	std::string directory = "LUA";
	for (const auto & entry : fs::directory_iterator(directory))
	{
		std::cout << entry.path().string() << std::endl;
		luaL_loadfile(_state, entry.path().string().c_str());
		lua_call(_state, 0, 0);
		startLua();
		lua_close;
	}
	//DEBUG WITH ONE SCRIPT
	//luaL_loadfile(_state, "LUA/Boost.lua");
	//lua_call(_state, 0, 0);
	//startLua();
}

void State_Game::registerFunctions()
{
	lua_newtable(_state);
		lua_pushcfunction(_state, State_Game::createSprite);
			lua_setfield(_state, -2, "create");
		lua_pushcfunction(_state, State_Game::positionSprite);
			lua_setfield(_state, -2, "position");
		lua_pushcfunction(_state, State_Game::scaleSprite);
			lua_setfield(_state, -2, "scale");
	lua_setglobal(_state, "Sprite");

	lua_newtable(_state);
		lua_pushcfunction(_state, State_Game::createCard);
			lua_setfield(_state, -2, "create");
		lua_pushcfunction(_state, State_Game::showCardAtStart);
			lua_setfield(_state, -2, "show");
		lua_pushcfunction(_state, State_Game::doDamage);
			lua_setfield(_state, -2, "doDamage");
		lua_pushcfunction(_state, State_Game::addHealth);
			lua_setfield(_state, -2, "addHealth");
		lua_pushcfunction(_state, State_Game::freezeEnemy);
			lua_setfield(_state, -2, "freeze");
		lua_pushcfunction(_state, State_Game::boostDamage);
			lua_setfield(_state, -2, "boost");
		lua_pushcfunction(_state, State_Game::reduceMana);
			lua_setfield(_state, -2, "reduce");
	lua_setglobal(_state, "Card");

}

void State_Game::startLua()
{
	lua_getglobal(_state, "OnCreate");
	if (lua_isfunction(_state, -1))
	{
		if (lua_pcall(_state, 0, 0, 0) != 0)
		{
			printf("Error %s\n", lua_tostring(_state, -1));
			exit(-1);
		}
	}

	lua_getglobal(_state, "Info");
	int damage = getIntField(_state, "Damage");
	int health = getIntField(_state, "Health");
	int mana = getIntField(_state, "Mana");
	std::string title = getStringField(_state, "Name");
	std::string description = getStringField(_state, "Description");


	GetGameObject(title)->SetDamage(damage);
	GetGameObject(title)->SetHealth(health);
	GetGameObject(title)->SetManaCost(mana);
	GetGameObject(title)->SetDescription(description);
}

void State_Game::updateLua()
{
	lua_getglobal(_state, "Update");
	if (lua_isfunction(_state, -1))
	{
		if (lua_pcall(_state, 0, 0, 0) != 0)
		{
			printf("Error %s\n", lua_tostring(_state, -1));
			exit(-1);
		}
	}
}

void State_Game::OnEnableCard()
{
	lua_getglobal(_state, "OnEnable");
	if (lua_isfunction(_state, -1))
	{
		if (lua_pcall(_state, 0, 0, 0) != 0)
		{
			printf("Error %s\n", lua_tostring(_state, -1));
			exit(-1);
		}
	}
}

void State_Game::OnDisableCard()
{
	lua_getglobal(_state, "OnDisable");
	if (lua_isfunction(_state, -1))
	{
		if (lua_pcall(_state, 0, 0, 0) != 0)
		{
			printf("Error %s\n", lua_tostring(_state, -1));
			exit(-1);
		}
	}
}

#pragma region LUAFunctions

int State_Game::createSprite(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		std::string name = (std::string) lua_tostring(pState, 1);
		std::string directory = (std::string) lua_tostring(pState, 2);

		sf::Texture texture;
		texture.loadFromFile(directory);
		std::cout << "Sprite " << name << " has been craeted from " << directory << std::endl;
		sf::Sprite sprite;
		sprite.setTexture(texture);
		GameObject** gameObject = (GameObject**)lua_newuserdata(pState, sizeof(GameObject*));
		*gameObject = new GameObject(sprite, texture, directory, name);

		luaL_getmetatable(pState, "Sprite");
		lua_setmetatable(pState, -2);
		_gameObjects->push_back(*gameObject);
		return 1;
	}
	return luaL_error(pState, "Sprite.create(name, directory), faulty arguments.");
}

int State_Game::scaleSprite(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		sf::Vector2f scale = sf::Vector2f(lua_tonumber(pState, 2), lua_tonumber(pState, 3));
		GameObject** obj = (GameObject**)lua_touserdata(pState, 1);
		(*obj)->Scale(scale);
		return 0;
	}
	return luaL_error(pState, "Sprite.scale(name, scale), faulty arguments.");
}

int State_Game::positionSprite(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		sf::Vector2f position = sf::Vector2f(lua_tonumber(pState, 2), lua_tonumber(pState, 3));
		GameObject** obj = (GameObject**)lua_touserdata(pState, 1);
		(*obj)->SetPosition(position);
		return 0;
	}
	return luaL_error(pState, "Sprite.position(name, position), faulty arguments.");
}

int State_Game::createCard(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		std::string name = (std::string) lua_tostring(pState, 1);
		std::string directory = (std::string) lua_tostring(pState, 2);

		sf::Texture texture;
		texture.loadFromFile(directory);
		std::cout << "Card " << name << " has been craeted from " << directory << std::endl;
		sf::Sprite sprite;
		sprite.setTexture(texture);
		GameObject** gameObject = (GameObject**)lua_newuserdata(pState, sizeof(GameObject*));
		*gameObject = new GameObject(sprite, texture, directory, name);

		luaL_getmetatable(pState, "Card");
		lua_setmetatable(pState, -2);
		_gameObjects->push_back(*gameObject);
		return 1;
	}
	return luaL_error(pState, "Card.create(name, directory,damage,mana,health), faulty arguments.");
}

int State_Game::showCardAtStart(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		bool toShow = lua_toboolean(pState, 2);
		GameObject** obj = (GameObject**)lua_touserdata(pState, 1);
		(*obj)->SetIsOnBoard(toShow);
		return 1;
	}
	return luaL_error(pState, "Sprite.isAtStart(name, bool), faulty arguments.");
}

int State_Game::getIntField(lua_State* L, const char* key)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);

	int result = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return result;
}

std::string State_Game::getStringField(lua_State* L, const char* key)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);

	std::string result = lua_tostring(L, -1);
	lua_pop(L, 1);
	return result;
}

int State_Game::addHealth(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		int amount = lua_tonumber(pState, 1);		
		//add health
		return 0;
	}
	return luaL_error(pState, "Card.addHealth(amount), faulty arguments.");
}

int State_Game::doDamage(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		int damage = lua_tonumber(pState, 1);
		
		return 0;
	}
	return luaL_error(pState, "Card.doDamage(amount), faulty arguments.");
}

int State_Game::boostDamage(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		int amount = lua_tonumber(pState, 1);
		
		return 0;
	}
	return luaL_error(pState, "Card.boost(amount), faulty arguments.");
}

int State_Game::freezeEnemy(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		int amount = lua_tonumber(pState, 1);
		
		return 0;
	}
	return luaL_error(pState, "Card.freeze(amount), faulty arguments.");
}

int State_Game::reduceMana(lua_State* pState)
{
	if (lua_gettop(pState))
	{
		int amount = lua_tonumber(pState, 1);

		return 0;
	}
	return luaL_error(pState, "Card.reduce(amount), faulty arguments.");
}
#pragma endregion

#pragma endregion

