#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <vector>
#include <unordered_map>
#include "../../Logic/States/State_Intro.hpp"
#include "../../Logic/States/State_Game.hpp"
#include "../../Logic/States/State_MainMenu.hpp"
#include "../../Logic/States/State_Paused.hpp"
#include "../../Logic/States/State_Win.hpp"
#include "../../Logic/States/State_GameOver.hpp"
#include "../../SharedContext.hpp"

enum class StateType
{
	Intro = 1,
	MainMenu,
	Game,
	Paused,
	GameOver,
	Credits,
	Win
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager(SharedContext* pShared);
	~StateManager();

	void Update(const sf::Time& pTime);
	void Draw();
	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& pType);

	void SwitchTo(const StateType& pType);
	void Remove(const StateType& pType);
private:
	void CreateState(const StateType& pType);
	void RemoveState(const StateType& pType);

	template<class T>
	void RegisterState(const StateType& pType)
	{
		_stateFactory[pType] = [this]()->BaseState*
		{
			return new T(this);
		};

	}

	SharedContext* _sharedContex;
	StateContainer _states;
	TypeContainer _toRemove;
	StateFactory _stateFactory;
};

#endif