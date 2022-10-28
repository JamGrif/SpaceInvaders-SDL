#pragma once
#include "gameobjects/SDLGameObject.h"

/// <summary>
/// Base class for a button object
/// </summary>
class Button :
    public SDLGameObject
{
public:
	Button();
	~Button();

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams) override;

	virtual void	drawObject() override;
	virtual void	updateObject() = 0;

	// Set what function is called when the button is pressed, called during OnEnterState function in current state
	void			setSelectCallback(void(*callback)()) { m_selectCallback = callback; }

	// The function callback ID is set in the level editor (.tmx file)
	uint8_t			getSelectCallbackID() const { return m_selectCallbackID; }

protected:

	// Ensure button is only clicked once until mouse button is released
	bool			m_bReleased;

	// Function pointer to store what function will run when the button is clicked on
	void (*m_selectCallback)();

	// ID of function used to determine which function to call on click (ID set in level editor)
	uint8_t			m_selectCallbackID;
};
