#pragma once

class GameObject;
class Level;

/// <summary>
/// Base class for the game state Finite State Machine
/// </summary>
class BaseState
{
public:
	virtual bool onEnterState() = 0;
	virtual bool onExitState() = 0;

	virtual void updateState();
	virtual void renderState();

	// Used for the GameStateMachine
	virtual std::string getStateID() const = 0;

protected:

	typedef void(*Callback)();

	void loadLevel(const std::string& level);
	virtual void setCallbacks();

	std::vector<Callback> m_stateCallbackFunctions;

	Level* m_pStateLevel;
};

