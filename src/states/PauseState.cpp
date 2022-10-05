#include "pch.h"
#include "states/PauseState.h"

#include "core/Game.h"
#include "core/SpriteManager.h"
#include "gameobjects/MenuButton.h"
#include "states/MainMenuState.h"
#include "states/utility/GameStateMachine.h"

#include "level/Level.h"
#include "level/ObjectLayer.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::updateState()
{
	BaseState::updateState();
	//m_pStateLevel->update();
}

void PauseState::renderState()
{
	BaseState::renderState();
	//m_pStateLevel->render();
}

bool PauseState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering PauseState-=-=-=-=-=-" << std::endl;

	loadLevel("PauseState.tmx");

	m_stateCallbackFunctions.push_back(0);
	m_stateCallbackFunctions.push_back(s_resumePlay);
	m_stateCallbackFunctions.push_back(s_pauseToMain);

	setCallbacks();

	return true;
}

bool PauseState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PauseState-=-=-=-=-=-" << std::endl;

	delete m_pStateLevel;

	return true;
}



void PauseState::s_pauseToMain()
{
	//TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	TheGame::Instance()->getStateMachine()->indicateAChange(StateMachineAction::PauseToMain);
}

void PauseState::s_resumePlay()
{
	//TheGame::Instance()->getStateMachine()->popState();
	TheGame::Instance()->getStateMachine()->indicateAChange(StateMachineAction::ResumePlay);
}


