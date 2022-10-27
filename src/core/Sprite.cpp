#include "pch.h"
#include "core/Sprite.h"

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "core/Renderer.h"

Sprite::Sprite()
	:m_pSurfaceObject(nullptr), m_pTextureObject(nullptr), m_filepath(""), m_id(""), m_spriteType(SpriteType::UNSET_SPRITE), m_bSpriteSetup(false),
	m_pIndivdualSpriteDimension(std::make_unique<SDL_Rect>()), m_pTotalSpriteDimensions(std::make_unique<SDL_Rect>()), m_scale(1, 1)
{
}

Sprite::~Sprite()
{
	if (m_pSurfaceObject)
		SDL_FreeSurface(m_pSurfaceObject);

	if (m_pTextureObject)
		SDL_DestroyTexture(m_pTextureObject);

	/*std::cout << "destroyed sprite " << m_id << std::endl;*/
}


bool Sprite::loadSprite(const std::string& filepath, const std::string& id, SpriteType spriteType)
{
	// Create SDL_Surface and SDL_Texture at filepath
	m_pSurfaceObject = IMG_Load(filepath.c_str());
	if (!m_pSurfaceObject)
		return false;

	m_pTextureObject = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), m_pSurfaceObject);
	if (!m_pTextureObject)
	{
		SDL_FreeSurface(m_pSurfaceObject);
		return false;
	}

	m_filepath = filepath;
	m_id = id;
	m_spriteType = spriteType;

	/*std::cout << "created sprite " << m_id << std::endl; */
	return true;
}


bool Sprite::loadSprite(SDL_Texture* pCreatedTexture, const spriteID& id, SpriteType spriteType)
{
	if (!pCreatedTexture)
		return false;

	m_id = id;
	m_pTextureObject = pCreatedTexture;
	m_spriteType = spriteType;

	/*std::cout << "created sprite " << m_id << std::endl;*/
	return true;
}

/// <summary>
/// Determine dimensions of an individual sprite frame by telling sprite how many sprite frames in a row
/// Takes into account the margin and spacing between each sprite frame
/// Assuming each frame has the exact same dimensions
/// </summary>
void Sprite::setUpIndividualSpriteDimensions(int numFrames, int numRows)
{
	if (m_bSpriteSetup)
		return;

	if (!m_pTextureObject)
		return;

	m_bSpriteSetup = true;

	// Store the complete dimensions of the sprite
	SDL_QueryTexture(m_pTextureObject, NULL, NULL, &m_pTotalSpriteDimensions->w, &m_pTotalSpriteDimensions->h);

	// Remove added space from sprite pixel margin and spacing
	m_pTotalSpriteDimensions->w -= SPRITE_PIXEL_MARGIN * 2;
	int temp = numFrames;
	m_pTotalSpriteDimensions->w -= SPRITE_PIXEL_SPACING * (--temp);


	m_pTotalSpriteDimensions->h -= SPRITE_PIXEL_MARGIN * 2;
	int temp2 = numRows;
	m_pTotalSpriteDimensions->h -= SPRITE_PIXEL_SPACING * (--temp2);

	// Width of each frame
	m_pIndivdualSpriteDimension->w = (m_pTotalSpriteDimensions->w / numFrames);

	// Height of each frame
	m_pIndivdualSpriteDimension->h = (m_pTotalSpriteDimensions->h / numRows);
}

/// <summary>
/// Update the total sprite dimensions to the current SDL_Texture size
/// </summary>
void Sprite::calculateSpriteDimensions()
{
	if (m_pTextureObject)
		SDL_QueryTexture(m_pTextureObject, NULL, NULL, &m_pTotalSpriteDimensions->w, &m_pTotalSpriteDimensions->h);
}

/// <summary>
/// Copy the totalSpriteDimensions to the provided SDL_Rect structure
/// </summary>
void Sprite::getSpriteDimensions(SDL_Rect& rect)
{
	rect.w = m_pTotalSpriteDimensions->w;
	rect.h = m_pTotalSpriteDimensions->h;
}

/// <summary>
/// Swap out the current SDL_Texture object with a new one
/// </summary>
void Sprite::changeTexture(SDL_Texture* pNewTexture)
{
	if (!pNewTexture)
		return;

	SDL_DestroyTexture(m_pTextureObject);
	m_pTextureObject = pNewTexture;
}
