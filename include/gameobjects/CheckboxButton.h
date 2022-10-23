#pragma once
#include "gameobjects/Button.h"

/// <summary>
/// Checkbox style button that calls a specified function when clicked on
/// </summary>
class CheckboxButton :
    public Button
{
public:
	CheckboxButton();
	~CheckboxButton();

	virtual void	loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void	drawObject();
	virtual void	updateObject();

	void			setCheckboxStateCallback(bool(*callback)()) { m_checkboxStateCallback = callback; }
	uint8_t			getCheckboxCallbackID() const { return m_checkboxStateCallbackID; }

private:

	bool m_bTicked;

	// Starting state of the checkbox (ticked or not)
	bool m_bInitialStateSet;

	// Function pointer to use to determine starting state of button
	bool (*m_checkboxStateCallback)();

	// ID of function used to determine starting state (ID set in level editor)
	uint8_t m_checkboxStateCallbackID; 
};

class CheckboxButtonCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<CheckboxButton>();
	}
};

