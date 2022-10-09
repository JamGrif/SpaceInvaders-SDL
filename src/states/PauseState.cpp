#include "pch.h"
#include "states/PauseState.h"

#include "core/Game.h"
#include "states/utility/GameStateMachine.h"

//#include "level/Level.h"
//#include "level/ObjectLayer.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::updateState()
{
	BaseState::updateState();
}

void PauseState::renderState()
{
	BaseState::renderState();
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

	BaseState::onExitState();

	//delete m_pStateLevel;

	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToMain);
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::popPause);
}


