#include "pch.h"
#include "gameobjects/SDLGameObject.h"

//#include "SDL.h"
#include "core/TextureManager.h"
#include "core/Renderer.h"

SDLGameObject::SDLGameObject()
	:GameObject(), m_position(0, 0), m_velocity(0, 0), m_acceleration(0,0)
{
	//m_width = pParams->getWidth();
	//m_height = pParams->getHeight();

	//m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TheTextureManager::Instance()->drawframe(m_textureID, static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_width, m_height, m_currentRow, m_currentFrame, true);
	}
	else
	{
		TheTextureManager::Instance()->drawframe(m_textureID, static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_width, m_height, m_currentRow, m_currentFrame, false);
	}
}

void SDLGameObject::update()
{
	// Allows gradual increase of velocity through acceleration
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::clean()
{

}

void SDLGameObject::load(const LoaderParams* pParams)
{
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	//m_numFrames = pParams->getNumFrames();
}
