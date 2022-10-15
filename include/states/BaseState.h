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
	virtual bool onExitState();

	virtual void updateState();
	virtual void renderState();

	// Used for the GameStateMachine
	virtual std::string getStateID() const = 0;

protected:

	// Callback function for Button objects to indicate what function to call when pressed
	typedef void(*Callback)();

	// Callback functions for CheckboxButton to indicate starting state of checkbox (filled or not)
	typedef bool(*CheckboxCallback)();

	// Callback functions for TextObjects to indicate what value to copy
	typedef std::string(*TextCallback)();

	void loadLevel(const std::string& filepath);

	virtual void setCallbacks();

	std::vector<Callback> m_stateCallbackFunctions;
	std::vector<CheckboxCallback> m_checkBoxStateCallbackFunctions;
	std::vector<TextCallback> m_textCallbackFunctions;

	Level* m_pStateLevel{nullptr};
};

