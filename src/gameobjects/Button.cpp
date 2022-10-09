#include "pch.h"
#include "gameobjects/Button.h"

Button::Button()
	:SDLGameObject(), m_bReleased(false), m_selectCallback(0), m_selectCallbackID(0)
{

}

Button::~Button()
{

}

void Button::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_selectCallbackID = pParams->selectCallbackID;
}

void Button::drawObject()
{
	SDLGameObject::drawObject();
}

void Button::updateObject()
{

}
