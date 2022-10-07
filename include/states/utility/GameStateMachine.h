#pragma once

class BaseState;

enum class StateMachineAction
{
	Nothing				= 0,
	Quit				= 1,
	changeToPlay		= 2,
	changeToMain		= 3,
	changeToGameOver	= 4,
	popPause			= 5,
	pushPause			= 6,
};

/// <summary>
/// Finite State Machine to handle the game states
/// </summary>
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	// State Actions
	void updateCurrentState();
	void renderCurrentState();

	bool checkForStateChange() const { return m_bNeedToChange; }
	void setStateUpdate(StateMachineAction change);
	void changeCurrentState();

private:
	std::vector<BaseState*> m_currentGameStates;

	// State Selection
	void pushState(BaseState* pState);		// Add a state without removing the previous state
	void changeState(BaseState* pState);	// Remove the previous state before adding another
	void popState();						// Remove the state currently being used without adding another

	bool m_bNeedToChange;
	StateMachineAction m_actionToTake;
};

