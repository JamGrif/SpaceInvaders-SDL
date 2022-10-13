#include "pch.h"
#include "core/Sprite.h"

#include "SDL2/SDL.h"

Sprite::Sprite(SDL_Texture* texture, const std::string& fileName, const std::string& id)
	:m_texture(texture), m_fileName(fileName), m_id(id), m_indivdualSpriteDimension(new SDL_Rect), m_totalSpriteDimensions(new SDL_Rect)
{
	// Store the complete dimensions of the sprite
	SDL_QueryTexture(m_texture, NULL, NULL, &m_totalSpriteDimensions->w, &m_totalSpriteDimensions->h);
}

Sprite::~Sprite()
{
	delete m_indivdualSpriteDimension;
	delete m_totalSpriteDimensions;

	SDL_DestroyTexture(m_texture);
}

/// <summary>
/// Determine how many individual sprite frames are in the sprite
/// Assuming each frame has the exact same dimensions
/// </summary>
void Sprite::setUpIndividualSpriteDimensions(int numFrames)
{
	m_indivdualSpriteDimension->w = m_totalSpriteDimensions->w / numFrames;
	m_indivdualSpriteDimension->h = m_totalSpriteDimensions->h;
}
