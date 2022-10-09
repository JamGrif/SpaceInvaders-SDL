#pragma once
#include "gameobjects/SDLGameObject.h"

class Button :
    public SDLGameObject
{
public:
	Button();
	~Button();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject() = 0; // Each button type has its own implementation of how it works

	void setSelectCallback(void(*callback)()) { m_selectCallback = callback; }
	int getSelectCallbackID() const { return m_selectCallbackID; }

protected:

	bool m_bReleased;
	void (*m_selectCallback)(); // function pointer to store what function will run when the button is clicked on
	int m_selectCallbackID;

};

