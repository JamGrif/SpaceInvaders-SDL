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
/// Finite State Machine to update and render the game states
/// Provides utility functions to swap out current states
/// </summary>
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	// State Actions
	void	updateCurrentState();
	void	renderCurrentState();

	bool	checkForStateChange() const { return m_bNeedToChange; }
	void	setStateUpdate(StateMachineAction change);
	void	changeCurrentState();

private:
	std::vector<std::unique_ptr<BaseState>> m_currentGameStates;

	// State Selection
	void	pushState(std::unique_ptr<BaseState> pState);
	void	changeState(std::unique_ptr<BaseState> pState);
	void	popState();

	bool	m_bNeedToChange;
	StateMachineAction m_actionToTake;
};

