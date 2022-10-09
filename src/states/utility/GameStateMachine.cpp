#include "pch.h"
#include "states/utility/GameStateMachine.h"

#include "states/BaseState.h"

#include "core/Game.h"
#include "core/SpriteManager.h"
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
	//std::cout << "hi4" << std::endl;
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
	//std::cout << "hi5" << std::endl;
	if (!m_currentGameStates.empty())
	{
		m_currentGameStates.back()->renderState();
	}
}

/// <summary>
/// Simply push the passed-in state into the gameStates array and then call its onEnter function
/// </summary>
void GameStateMachine::pushState(BaseState* pState)
{
	m_currentGameStates.push_back(pState);
	m_currentGameStates.back()->onEnterState();
}

/// <summary>
/// First check if there are any states in the array, and if so, check whether their stateID is the same as the current one, and if so, do nothing.
/// If the stateID does not match, then remove the current state, add the new pState and call its onEnter function
/// </summary>
void GameStateMachine::changeState(BaseState* pState)
{
	//if (!m_currentGameStates.empty())
	//{
	//	if (m_currentGameStates.back()->getStateID() == pState->getStateID())
	//		return;
	//}

	// Pop all remaining states left before changing state
	while (!m_currentGameStates.empty())
	{
		popState();
	}

	TheSpriteManager::Instance()->clearAllFromSpriteMap();

	// Push back the new state
	m_currentGameStates.push_back(pState);

	// Initialize it
	m_currentGameStates.back()->onEnterState();
}

/// <summary>
/// First check if there are any states available, and if so, call the onExit function of the state and then remove it
/// </summary>
void GameStateMachine::popState()
{
	if (m_currentGameStates.empty())
		return;

	m_currentGameStates.back()->onExitState();
	delete m_currentGameStates.back();
	m_currentGameStates.pop_back();
}

void GameStateMachine::setStateUpdate(StateMachineAction change)
{
	m_bNeedToChange = true;
	m_actionToTake = change;
}

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
