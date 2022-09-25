#pragma once
#include "SDLGameObject.h"
class MenuButton :
    public SDLGameObject
{
public:
	MenuButton(const LoaderParams* pParams, void(*callback)());

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	bool m_bReleased;
	void (*m_callback)(); // function pointer to store what function will run when the button is clicked on
};

