#include "SDLGameObject.h"


#include "SDLRenderer.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
	:GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0,0)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TheTextureManager::Instance()->drawframe(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheRenderer::Instance()->getRendererPtr(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TheTextureManager::Instance()->drawframe(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheRenderer::Instance()->getRendererPtr());
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
