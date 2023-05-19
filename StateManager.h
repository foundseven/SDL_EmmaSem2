#pragma once
#include <vector>

class State;

class StateManager
{
private: // Public Properties
	static std::vector<State*> s_states;

public: // Pulbic Methods
	static void Update(float deltaTime);
	static void Render();
	static void PushState(State* pState); // Used when going to PauseState
	static void PopState(); // Used when leaving PauseState
	static void ChangeState(State* pState);
	static void Quit(); // Used for cleanup
	static std::vector<State*>& GetStates(); // Returns a reference to our State* vector

private: // Private methods
	StateManager() {}
};
