#include "pch.h"
#include "states/utility/GameStateMachine.h"

#include "core/Game.h"
#include "core/SpriteManager.h"
#include "states/BaseState.h"
#include "states/PlayState.h"
#include "states/MainMenuState.h"
#include "states/PauseState.h"
#include "states/GameOverState.h"

GameStateMachine::GameStateMachine()
	:m_bNeedToChange(false), m_actionToTake(StateMachineAction::Nothing)
{
}

GameStateMachine::~GameStateMachine()
{
	SpriteManager::Instance()->clearAllFromSpriteMap();

	// Pop all remaining states left
	while (!m_currentGameStates.empty())
	{
		popState();
	}
}

/// <summary>
/// Update the currently selected state
/// </summary>
void GameStateMachine::updateCurrentState()
{
	if (!m_currentGameStates.empty())
	{
		m_currentGameStates.back()->updateState();
	}
}

/// <summary>
/// Render the currently selected state
/// </summary>
void GameStateMachine::renderCurrentState()
{
	if (!m_currentGameStates.empty())
	{
		m_currentGameStates.back()->renderState();
	}
}

/// <summary>
/// Push the passed-in state into the gameStates vector and then call its onEnterState function
/// </summary>
void GameStateMachine::pushState(BaseState* pState)
{
	assert(pState);

	m_currentGameStates.push_back(pState);
	m_currentGameStates.back()->onEnterState();
}

/// <summary>
/// Change the state to specified state, popping any states currently loaded
/// </summary>
void GameStateMachine::changeState(BaseState* pState)
{
	assert(pState);

	// Pop all remaining states left before changing state
	while (!m_currentGameStates.empty())
	{
		popState();
	}

	// Clear all sprites used in this state
	TheSpriteManager::Instance()->clearAllFromSpriteMap();

	// Push back the new state
	m_currentGameStates.push_back(pState);

	// Initialize it
	m_currentGameStates.back()->onEnterState();
}

/// <summary>
/// First check if there are any states available, and if so, call the onExitState function of the state and then remove it
/// </summary>
void GameStateMachine::popState()
{
	// Ensure that are states to pop off
	if (m_currentGameStates.empty())
		return;

	m_currentGameStates.back()->onExitState();
	delete m_currentGameStates.back();
	m_currentGameStates.pop_back();
}

/// <summary>
/// Specify what state action to perform in next frame
/// </summary>
void GameStateMachine::setStateUpdate(StateMachineAction change)
{
	m_bNeedToChange = true;
	m_actionToTake = change;
}

/// <summary>
/// Perform state action on state machine
/// Action to take indicated through setStateUpdate function
/// </summary>
void GameStateMachine::changeCurrentState()
{
	switch (m_actionToTake)
	{
		case StateMachineAction::Quit:
			TheGame::Instance()->quitGame();
			break;

		case StateMachineAction::changeToPlay:
			changeState(new PlayState());
			break;

		case StateMachineAction::changeToMain:
			changeState(new MainMenuState());
			break;

		case StateMachineAction::changeToGameOver:
			changeState(new GameOverState());
			break;

		case StateMachineAction::popPause:
			popState();
			break;

		case StateMachineAction::pushPause:
			pushState(new PauseState());
			break;
	}

	// Reset values
	m_actionToTake = StateMachineAction::Nothing;
	m_bNeedToChange = false;
}
