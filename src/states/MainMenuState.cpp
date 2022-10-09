#include "pch.h"
#include "states/MainMenuState.h"

#include "core/Game.h"
#include "states/utility/GameStateMachine.h"
#include "core/SoundManager.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToPlay);
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::Quit);
}

void MainMenuState::s_toggleSound()
{
	TheSoundManager::Instance()->toggleSound();
}


void MainMenuState::s_toggleMusic()
{
	TheSoundManager::Instance()->toggleMusic();
}


bool MainMenuState::s_checkboxState1()
{
	return TheSoundManager::Instance()->isSoundPlaying();
}


bool MainMenuState::s_checkboxState2()
{
	return TheSoundManager::Instance()->isMusicPlaying();
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
	m_stateCallbackFunctions.push_back(s_toggleSound);
	m_stateCallbackFunctions.push_back(s_toggleMusic);

	m_checkBoxStateCallbackFunctions.push_back(0);
	m_checkBoxStateCallbackFunctions.push_back(s_checkboxState1);
	m_checkBoxStateCallbackFunctions.push_back(s_checkboxState2);

	// Set the callbacks for menu items
	setCallbacks();

	return true;
}

bool MainMenuState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting MenuState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	//delete m_pStateLevel;

	return true;
}


