#include "StateManager.h"
#include "States.h"


//to fully understand this, you need to understand your states. each one reps a diff part of yr game. each one will have similar functions or different ones, like title vs menu.
//this is so we can actually transfer between the states easily. this way we can render from one to the other instead of always running one long heavy one.
//pause state is so we can just pause it as a whole... only one that can kinda hover above if you will


std::vector<State*> StateManager::s_states;

void StateManager::Update(float deltaTime)
{
	if(!s_states.empty())
	{
		// s_states.back() represents the current state, by pointer
		s_states.back()->Update(deltaTime);
	}
}

// Invokes Render() of the current state
void StateManager::Render()
{
	if(!s_states.empty())
	{
		s_states.back()->Render();
	}
}

void StateManager::PushState(State* pState)
{
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::PopState()
{
	// If only one state in vector, return
	if(s_states.size() <= 1)
		return;

	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	s_states.back()->Resume();
}

void StateManager::ChangeState(State* pState) 
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates()
{
	return s_states;
}