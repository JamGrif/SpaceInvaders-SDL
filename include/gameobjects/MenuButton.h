#pragma once
#include "SDLGameObject.h"


class MenuButton :
    public SDLGameObject
{
public:
	MenuButton();
	~MenuButton();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

	void setCallback(void(*callback)());
	int getCallbackID();

private:

	bool m_bReleased;
	void (*m_callback)(); // function pointer to store what function will run when the button is clicked on
	int m_callbackID;
};

class MenuButtonCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new MenuButton();
	}
};
