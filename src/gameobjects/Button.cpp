#include "pch.h"
#include "gameobjects/Button.h"

Button::Button()
	:SDLGameObject(), m_bReleased(false), m_selectCallbackID(0), m_selectCallback(nullptr)
{
}


Button::~Button()
{
}

/// <summary>
/// Set all values in Button class and parent classes
/// </summary>
void Button::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_selectCallbackID = pParams->selectCallbackID;
}

/// <summary>
/// Call parent class draw function
/// </summary>
void Button::drawObject()
{
	SDLGameObject::drawObject();
}
