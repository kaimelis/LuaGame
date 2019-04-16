#ifndef STATEGAME_HPP
#define STATEGAME_HPP

#include "../../Core/StateSystem/BaseState.hpp"
#include "../../Core/EventSystem/EventManager.hpp"
#include "../../Core//ECS/GameObject.hpp"

extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
#include <lua.hpp>
}

class State_Game : public BaseState
{
public:
	State_Game(StateManager* pStateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& pTime);
	void Draw();

	void MainMenu(EventDetails* pDetails);
	void Pause(EventDetails* pDetails);
	void MouseClick(EventDetails* pDetails);

private:
	//////////////////////////////////////////////
	//		HUD
	//////////////////////////////////////////////
#pragma region HUD
	sf::Font _font;

	sf::Vector2f _buttonSize;
	sf::Vector2f _buttonPos;
	unsigned int _buttonPadding;
	sf::Sprite _background;
	sf::Texture _bakgroundTexture;
	sf::RectangleShape _rects;
	sf::Text _buttonText;
	sf::Text debugText;

	void initialiseHUD();
	void UpdateHUDInformation();

	sf::Text _playerHealth;
	sf::Text _enemyHealth;
	sf::Text _playerMana;

	sf::Text _damageCard;
#pragma endregion
	   	 
	////////////////////////////////////////////////
	//			LOGIC
	///////////////////////////////////////////////
#pragma region Logic
	static std::vector<GameObject*>* _gameObjects;
	bool playerTurn = true;

	int playerHealth = 20;
	int playerMana = 5;
	int _deckAmount = 10;
	int _cardsInHand = 0;
	bool isCardHandFull = true;
	bool isDeckEmpty = false;

	int enemyHealth = 20;
	int enemyDamage = 1;
	void EnemyTurn();
	void CheckCards(std::string pName);

	float _timePassed;
	bool _activateTimer = false;

	GameObject* GetGameObject(std::string pName);
#pragma endregion


#pragma region LUA
	lua_State* _state;
	void registerFunctions();
	void initialiseLua();
	void startLua();
	void updateLua();

	void registerCards();
	void OnEnableCard();
	void OnDisableCard();


	/////////////////////////////////////////////////////////
	//			Sprites
	/////////////////////////////////////////////////////////
	static int createSprite(lua_State* pState);
	static int scaleSprite(lua_State* pState);
	static int positionSprite(lua_State* pState);
	////////////////////////////////////////////////////////////
	//		CARDS
	///////////////////////////////////////////////////////////
	static int createCard(lua_State* pState);
	static int showCardAtStart(lua_State* pState);
	static int getIntField(lua_State* L, const char* key);
	static std::string getStringField(lua_State* L, const char* key);
	static int boostDamage(lua_State* pState);
	static int addHealth(lua_State* pState);
	static int freezeEnemy(lua_State* pState);
	static int doDamage(lua_State* pState);
	static int reduceMana(lua_State* pState);
#pragma endregion


};

#endif