#pragma once

class GameState;

/// <summary>
/// Finite State Machine to handle the game states
/// </summary>
class GameStateMachine
{
public:

	// State Actions
	void update();
	void render();

	void pushState(GameState* pState);		// Add a state without removing the previous state
	void changeState(GameState* pState);	// Remove the previous state before adding another
	void popState();						// Remove the state currently being used without adding another

private:
	std::vector<GameState*> m_gameStates;

};

