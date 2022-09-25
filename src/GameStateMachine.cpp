#include "GameStateMachine.h"

/// <summary>
/// Run the update function of the currently selected state
/// </summary>
void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

/// <summary>
/// Run the render function of the currently selected state
/// </summary>
void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}

/// <summary>
/// Simply push the passed-in state into the gameStates array and then call its onEnter function
/// </summary>
void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

/// <summary>
/// First check if there are any states in the array, and if so, check wheter their stateID is the same as the current one, and if so, do nothing.
/// If the stateID does not match, then remove the current state, add the new pState and call its onEnter function
/// </summary>
void GameStateMachine::changeState(GameState* pState)
{
	//std::cout << "hi" << std::endl;

	if (!m_gameStates.empty())
	{
		//std::cout << m_gameStates.back()->getStateID() << std::endl;
		//std::cout << pState->getStateID() << std::endl;

		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}
		//std::cout << "hi2" << std::endl;
		if (m_gameStates.back()->onExit())
		{
			//std::cout << "hi3" << std::endl;
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}

	// Push back our new state
	m_gameStates.push_back(pState);

	// Initialize it
	m_gameStates.back()->onEnter();
}

/// <summary>
/// First check if there are any states available, and if so, call the onExit function of the state and then remove it
/// </summary>
void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}
