#include "pch.h"
#include "states/PauseState.h"

#include "core/Game.h"
#include "core/InputHandler.h"
#include "states/utility/GameStateMachine.h"

const std::string PauseState::s_pauseID = "PAUSE";

/// <summary>
/// Set in editor: selectCallbackID 2
/// </summary>
void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToMain);
}

/// <summary>
/// Set in editor: selectCallbackID 1
/// </summary>
void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::popPause);
}

/// <summary>
/// Call parent class update function
/// </summary>
void PauseState::updateState()
{
	BaseState::updateState();
}

/// <summary>
/// Call parent class render function
/// </summary>
void PauseState::renderState()
{
	BaseState::renderState();
}

/// <summary>
/// Loads the level and sets the callback functions used in PauseState
/// </summary>
bool PauseState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering PauseState-=-=-=-=-=-" << std::endl;

	loadLevel("PauseState.tmx");

	// Assign IDs to functions, push 0 first so IDs start at 1
	m_stateCallbackFunctions.push_back(0);
	m_stateCallbackFunctions.push_back(s_resumePlay);
	m_stateCallbackFunctions.push_back(s_pauseToMain);

	setCallbacks();

	return true;
}

/// <summary>
/// Call parent class onExitState function
/// </summary>
bool PauseState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PauseState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	return true;
}


