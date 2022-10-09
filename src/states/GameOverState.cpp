#include "pch.h"
#include "states/GameOverState.h"

#include "core/Game.h"
#include "core/SpriteManager.h"
#include "states/utility/GameStateMachine.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

std::string GameOverState::s_textCallback1()
{
	return std::to_string(TheGame::Instance()->getCurrentScore());
}

std::string GameOverState::s_textCallback2()
{
	return TheGame::Instance()->getGameOutcome();
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToMain);
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToPlay);
}

void GameOverState::updateState()
{
	BaseState::updateState();
}

void GameOverState::renderState()
{
	BaseState::renderState();
}

bool GameOverState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering GameOverState-=-=-=-=-=-" << std::endl;

	loadLevel("GameOverState.tmx");

	m_stateCallbackFunctions.push_back(0);
	m_stateCallbackFunctions.push_back(s_gameOverToMain);
	m_stateCallbackFunctions.push_back(s_restartPlay);

	m_textCallbackFunctions.push_back(0);
	m_textCallbackFunctions.push_back(s_textCallback1);
	m_textCallbackFunctions.push_back(s_textCallback2);

	// Set the callbacks for menu items
	setCallbacks();

	

	return true;
}

bool GameOverState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting GameOverState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	//delete m_pStateLevel;

	return true;
}

