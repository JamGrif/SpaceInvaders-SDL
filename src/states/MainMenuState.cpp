#include "pch.h"
#include "states/MainMenuState.h"

#include "core/SpriteManager.h"
#include "core/Game.h"
#include "core/Renderer.h"
#include "gameobjects/MenuButton.h"
#include "gameobjects/BaseGameObject.h"
#include "states/PlayState.h"
#include "states/utility/GameStateMachine.h"

#include "level/Level.h"
#include "level/ObjectLayer.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->indicateAChange(StateMachineAction::MainMenuToPlay);
	//TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->getStateMachine()->indicateAChange(StateMachineAction::Quit);
	//TheGame::Instance()->quitGame();
}

void MainMenuState::updateState()
{
	BaseState::updateState();
}

void MainMenuState::renderState()
{
	BaseState::renderState();
}

bool MainMenuState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering MenuState-=-=-=-=-=-" << std::endl;

	loadLevel("MainMenuState.tmx");

	// Push any callbacks into the m_callbacks array, inherited from MenuState
	m_stateCallbackFunctions.push_back(0); // pushback = callbackID starts from 1
	m_stateCallbackFunctions.push_back(s_menuToPlay);
	m_stateCallbackFunctions.push_back(s_exitFromMenu);

	// Set the callbacks for menu items
	setCallbacks();

	return true;
}

bool MainMenuState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting MenuState-=-=-=-=-=-" << std::endl;
	

	delete m_pStateLevel;

	return true;
}


