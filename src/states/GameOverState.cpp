#include "pch.h"
#include "states/GameOverState.h"

#include "core/Game.h"
#include "core/SpriteManager.h"
#include "core/SoundManager.h"
#include "states/utility/GameStateMachine.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

/// <summary>
/// Set in editor: textCallbackID 1
/// </summary>
std::string GameOverState::s_textCallback1()
{
	return std::to_string(TheGame::Instance()->getCurrentScore());
}

/// <summary>
/// Set in editor: textCallbackID 2
/// </summary>
std::string GameOverState::s_textCallback2()
{
	return TheGame::Instance()->getGameOutcome();
}

/// <summary>
/// Set in editor: selectCallbackID 1
/// </summary>
void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToMain);
}

/// <summary>
/// Set in editor: selectCallbackID 2
/// </summary>
void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToPlay);
}

/// <summary>
/// Call parent class update function
/// </summary>
void GameOverState::updateState()
{
	BaseState::updateState();
}

/// <summary>
/// Call parent class render function
/// </summary>
void GameOverState::renderState()
{
	BaseState::renderState();
}

/// <summary>
/// Loads the level and sets the callback functions used in GameOverState
/// </summary>
bool GameOverState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering GameOverState-=-=-=-=-=-" << std::endl;

	loadLevel("GameOverState.tmx");

	// Assign IDs to functions, push 0 first so IDs start at 1
	m_stateCallbackFunctions.push_back(0);
	m_stateCallbackFunctions.push_back(s_gameOverToMain);
	m_stateCallbackFunctions.push_back(s_restartPlay);

	m_textCallbackFunctions.push_back(0);
	m_textCallbackFunctions.push_back(s_textCallback1);
	m_textCallbackFunctions.push_back(s_textCallback2);

	setCallbacks();

	TheSoundManager::Instance()->playSound("gameOver");

	return true;
}

/// <summary>
/// Call parent class onExitState function
/// </summary>
bool GameOverState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting GameOverState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	return true;
}

