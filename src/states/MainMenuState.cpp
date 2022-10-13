#include "pch.h"
#include "states/MainMenuState.h"

#include "core/Game.h"
#include "core/SoundManager.h"
#include "states/utility/GameStateMachine.h"

const std::string MainMenuState::s_menuID = "MENU";

/// <summary>
/// Set in editor: selectCallbackID 1
/// </summary>
void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToPlay);
}

/// <summary>
/// Set in editor: selectCallbackID 2
/// </summary>
void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::Quit);
}

/// <summary>
/// Set in editor: selectCallbackID 3
/// </summary>
void MainMenuState::s_toggleSound()
{
	TheSoundManager::Instance()->toggleSoundEffects();
}

/// <summary>
/// Set in editor: selectCallbackID 4
/// </summary>
void MainMenuState::s_toggleMusic()
{
	TheSoundManager::Instance()->toggleMusic();
}

/// <summary>
/// Set in editor: checkboxStateCallbackID 1
/// </summary>
bool MainMenuState::s_checkboxState1()
{
	return TheSoundManager::Instance()->isSoundPlaying();
}

/// <summary>
/// Set in editor: checkboxStateCallbackID 2
/// </summary>
bool MainMenuState::s_checkboxState2()
{
	return TheSoundManager::Instance()->isMusicPlaying();
}

/// <summary>
/// Call parent class update function
/// </summary>
void MainMenuState::updateState()
{
	BaseState::updateState();
}

/// <summary>
/// Call parent class render function
/// </summary>
void MainMenuState::renderState()
{
	BaseState::renderState();
}

/// <summary>
/// Loads the level and sets the callback functions used in MainMenuState
/// </summary>
bool MainMenuState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering MenuState-=-=-=-=-=-" << std::endl;

	loadLevel("MainMenuState.tmx");

	// Assign IDs to functions, push 0 first so IDs start at 1
	m_stateCallbackFunctions.push_back(0); 
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

/// <summary>
/// Call parent class onExitState function
/// </summary>
bool MainMenuState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting MenuState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	return true;
}


