#pragma once
#include "gameobjects/Button.h"

class CheckboxButton :
    public Button
{
public:
	CheckboxButton();
	~CheckboxButton();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

	void setCheckboxStateCallback(bool(*callback)()) { m_checkboxStateCallback = callback; }
	int getCheckboxCallbackID() const { return m_checkboxStateCallbackID; }

private:

	bool m_bTicked;

	bool m_bInitialStateSet;

	bool (*m_checkboxStateCallback)(); // function pointer to store what function will run when the button is clicked on
	int m_checkboxStateCallbackID; // Used to determine the starting state of the checkbox (ticked or not ticked) when first created

};

class CheckboxButtonCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new CheckboxButton();
	}
};

