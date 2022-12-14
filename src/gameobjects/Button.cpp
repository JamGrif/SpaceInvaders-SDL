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
void Button::loadObject(std::unique_ptr<LoaderParams> pParams)
{
	m_selectCallbackID = pParams->selectCallbackID;

	SDLGameObject::loadObject(std::move(pParams));
}

/// <summary>
/// Call parent class draw function
/// </summary>
void Button::drawObject()
{
	SDLGameObject::drawObject();
}
