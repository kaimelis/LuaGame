#include "StateManager.hpp"

StateManager::StateManager(SharedContext* pShared) : _sharedContex(pShared)
{
	RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Paused>(StateType::Paused);
	RegisterState<State_GameOver>(StateType::GameOver);
	RegisterState<State_Win>(StateType::Win);
}

StateManager::~StateManager()
{
	for (auto &itr : _states)
	{
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Update(const sf::Time& pTime)
{
	if (_states.empty())
		return;
	if (_states.back().second->IsTranscendent() && _states.size() > 1)
	{
		auto itr = _states.end();
		while (itr != _states.begin())
		{
			if (itr != _states.end())
			{
				if (!itr->second->IsTranscendent())
					break;
			}
			--itr;
		}

		for (; itr != _states.end(); ++itr)
		{
			itr->second->Update(pTime);
		}
	}
	else
		_states.back().second->Update(pTime);
}

void StateManager::Draw()
{
	if (_states.empty())
		return;
	if (_states.back().second->IsTransparent() && _states.size() > 1)
	{
		auto itr = _states.end();
		while (itr != _states.begin())
		{
			if (itr != _states.end())
			{
				if (!itr->second->IsTransparent())
					break;
			}
			--itr;
		}
		for (; itr != _states.end(); ++itr)
		{
			_sharedContex->_wind->GetRenderWindow()->setView(itr->second->GetView());
			itr->second->Draw();
		}
	}
	else
		_states.back().second->Draw();
}



SharedContext* StateManager::GetContext()
{
	return _sharedContex;
}

bool StateManager::HasState(const StateType& pType)
{
	for (auto itr = _states.begin(); itr != _states.end(); ++itr)
	{
		if (itr->first == pType)
		{
			auto removed = std::find(_toRemove.begin(), _toRemove.end(), pType);
			if (removed == _toRemove.end())	return true;
			return false;
		}
	}
	return false;

}

void StateManager::Remove(const StateType& pType)
{
	_toRemove.push_back(pType);
}

void StateManager::ProcessRequests()
{
	while (_toRemove.begin() != _toRemove.end())
	{
		RemoveState(*_toRemove.begin());
		_toRemove.erase(_toRemove.begin());
	}
}

void StateManager::SwitchTo(const StateType& pType)
{
	_sharedContex->_eventManager->SetCurrentState(pType);
	for (auto itr = _states.begin(); itr != _states.end(); ++itr)
	{
		if (itr->first == pType)
		{
			_states.back().second->Deactivate();
			StateType type = itr->first;
			BaseState* state = itr->second;
			_states.erase(itr);
			_states.emplace_back(type, state);
			state->Activate();
			_sharedContex->_wind->GetRenderWindow()->setView(state->GetView());
			return;
		}
	}

	if (!_states.empty())
	{
		_states.back().second->Deactivate();
	}
	CreateState(pType);
	_states.back().second->Activate();
	_sharedContex->_wind->GetRenderWindow()->setView(_states.back().second->GetView());
}

void StateManager::CreateState(const StateType& pType)
{
	auto newState = _stateFactory.find(pType);
	if (newState == _stateFactory.end()) { return; }
	BaseState* state = newState->second();
	state->_view = _sharedContex->_wind->GetRenderWindow()->getDefaultView();
	_states.emplace_back(pType, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& pType) {
	for (auto itr = _states.begin();
		itr != _states.end(); ++itr)
	{
		if (itr->first == pType) {
			itr->second->OnDestroy();
			delete itr->second;
			_states.erase(itr);
			return;
		}
	}
}