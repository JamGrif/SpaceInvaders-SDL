#include "pch.h"
#include "core/Sprite.h"

#include "SDL2/SDL.h"

Sprite::Sprite(SDL_Texture* texture, const std::string& fileName, const std::string& id)
	:m_textureObject(texture), m_fileName(fileName), m_id(id),
	m_indivdualSpriteDimension(std::make_unique<SDL_Rect>()), m_totalSpriteDimensions(std::make_unique<SDL_Rect>()), m_bSpriteSetup(false)
{
	/*std::cout << "created sprite " << m_fileName << std::endl;*/
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_textureObject);

	/*std::cout << "destroyed sprite " << m_fileName << std::endl;*/
}

/// <summary>
/// Determine dimensions of an individual sprite frame by telling sprite how many sprite frames in a row
/// Takes into account the margin and spacing between each sprite frame
/// Assuming each frame has the exact same dimensions
/// </summary>
void Sprite::setUpIndividualSpriteDimensions(int numFrames)
{
	if (m_bSpriteSetup)
		return;

	m_bSpriteSetup = true;

	// Store the complete dimensions of the sprite
	SDL_QueryTexture(m_textureObject, NULL, NULL, &m_totalSpriteDimensions->w, &m_totalSpriteDimensions->h);

	// Remove added space from sprite pixel margin and spacing
	m_totalSpriteDimensions->w -= SPRITE_PIXEL_MARGIN * 2;
	int temp = numFrames;
	m_totalSpriteDimensions->w -= SPRITE_PIXEL_SPACING * (--temp);

	m_totalSpriteDimensions->h -= (SPRITE_PIXEL_MARGIN * 2);

	// Width of each frame
	m_indivdualSpriteDimension->w = (m_totalSpriteDimensions->w / numFrames);

	// Height of each frame
	m_indivdualSpriteDimension->h = m_totalSpriteDimensions->h;
}
