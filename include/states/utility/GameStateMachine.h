#pragma once

class BaseState;

enum class StateMachineAction
{
	Nothing			= 0,
	Quit			= 1,
	MainMenuToPlay	= 2,
	PauseToMain		= 3,
	ResumePlay		= 4,
	GameOverToMain	= 5,
	RestartPlay		= 6,
	Pause			= 7,
	GameOver		= 8,
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

	// State Selection
	void pushState(BaseState* pState);		// Add a state without removing the previous state
	void changeState(BaseState* pState);	// Remove the previous state before adding another
	void popState();						// Remove the state currently being used without adding another

	bool IsActionToChange() { return m_bNeedToChange; }
	void indicateAChange(StateMachineAction change);
	void doAChange();

private:
	std::vector<BaseState*> m_currentGameStates;

	bool m_bNeedToChange;
	StateMachineAction m_actionToTake;
};

