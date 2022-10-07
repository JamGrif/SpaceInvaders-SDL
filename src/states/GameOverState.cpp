#include "pch.h"
#include "states/GameOverState.h"

#include "core/Game.h"
#include "core/SpriteManager.h"
#include "gameobjects/MenuButton.h"
#include "gameobjects/BaseGameObject.h"
#include "states/PlayState.h"
#include "states/MainMenuState.h"
#include "states/utility/GameStateMachine.h"

#include "level/Level.h"
#include "level/ObjectLayer.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	//TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToMain);
}

void GameOverState::s_restartPlay()
{
	//TheGame::Instance()->getStateMachine()->changeState(new PlayState());
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

	// Set the callbacks for menu items
	setCallbacks();

	return true;
}

bool GameOverState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting GameOverState-=-=-=-=-=-" << std::endl;

	delete m_pStateLevel;

	return true;
}

