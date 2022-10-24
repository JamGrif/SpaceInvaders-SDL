#include "pch.h"
#include "core/SpriteManager.h"

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "core/Renderer.h"

/// <summary>
/// Create sprite at filepath and assign an id to it
/// </summary>
bool SpriteManager::loadSprite(const std::string& filepath, const std::string& id)
{
	// Check if sprite at filepath already exists
	if (m_spriteMap.find(id) != m_spriteMap.end())
		return false;

	// Create SDL_Texture at filepath
	SDL_Surface* pTempSurface = IMG_Load(filepath.c_str());
	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (!pTexture)
		return false;

	// Add sprite to spriteMap
	m_spriteMap.insert({ id, std::make_shared<Sprite>(pTexture, filepath, id) });

	return true;
}

/// <summary>
/// Load a collection of sprites using the filepath and id from the pair structure
/// </summary>
bool SpriteManager::loadSprite(const std::vector<std::pair<std::string, std::string>>& spritesToLoad)
{
	// Loop through and load each sprite using its filepath(first) and id(second)
	for (const auto& s : spritesToLoad)
	{
		loadSprite(s.first, s.second);
	}

	return true;
}

/// <summary>
/// Create a Sprite object from an already created SDL_Texture and assign an id to it
/// </summary>
bool SpriteManager::loadSprite(SDL_Texture* pCreatedTexture, const std::string& id)
{
	// Check if sprite with id already exists
	if (m_spriteMap.find(id) != m_spriteMap.end())
		return false;

	// Add sprite to spriteMap
	m_spriteMap.insert({ id, std::make_shared<Sprite>(pCreatedTexture, "", id)});

	return true;
}

/// <summary>
/// Delete all loaded sprite objects from the spriteMap
/// </summary>
void SpriteManager::clearAllFromSpriteMap()
{
	m_spriteMap.clear();

	// As all sprites have been removed, clear free IDs
	resetIDs();
}

/// <summary>
/// Delete the specified loaded sprite object from the spriteMap
/// </summary>
void SpriteManager::clearFromSpriteMap(const std::string& id)
{
	if (m_spriteMap.find(id) != m_spriteMap.end())
		m_spriteMap.erase(id);
}

/// <summary>
/// Draw the specified sprite, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteFrame(const std::string& id, const SDL_Rect& objectAttributes, uint8_t currentFrame, bool flipHorizontal, double spriteRotation)
{
	if (m_spriteMap.find(id) == m_spriteMap.end())
	{
		std::cout << "sprite with id: " << id << " doesn't exist" << std::endl;
		return;
	}

	SDL_Rect spriteFrame; // What part of the sprite sheet to use

	spriteFrame.x = ((objectAttributes.w * currentFrame) + SPRITE_PIXEL_MARGIN) + currentFrame * SPRITE_PIXEL_SPACING;
	spriteFrame.y = SPRITE_PIXEL_MARGIN;
	spriteFrame.w = objectAttributes.w;
	spriteFrame.h = objectAttributes.h;

	SDL_RendererFlip flag = flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), &spriteFrame, &objectAttributes, spriteRotation, 0, flag);
}

/// <summary>
/// Draw the specified tileset tile, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteTile(const std::string& id, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t currentRow, uint8_t currentFrame)
{
	if (m_spriteMap.find(id) == m_spriteMap.end())
	{
		std::cout << "tileset with id: " << id << " doesn't exist" << std::endl;
		return;
	}

	SDL_Rect tileToDraw;	// Tile on tileset to draw
	SDL_Rect destRect;		

	tileToDraw.x = m_tilesetPixelMargin + (m_tilesetPixelSpacing + width) * currentFrame;
	tileToDraw.y = m_tilesetPixelMargin + (m_tilesetPixelSpacing + height) * currentRow;
	tileToDraw.w = destRect.w = width;
	tileToDraw.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), &tileToDraw, &destRect, 0, 0, SDL_FLIP_NONE);
}

/// <summary>
/// Draw the specified text, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteText(const std::string& id, const SDL_Rect& objectAttributes)
{
	if (m_spriteMap.find(id) == m_spriteMap.end())
	{
		std::cout << "text sprite with id: " << id << " doesn't exist" << std::endl;
		return;
	}

	SDL_RenderCopy(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), NULL, &objectAttributes);
}

/// <summary>
/// Return sprite object at id, nullptr if doesn't exist
/// </summary>
std::weak_ptr<Sprite> SpriteManager::getSpriteViaID(const std::string& id) const
{
	return m_spriteMap.find(id) != m_spriteMap.end() ? m_spriteMap.at(id) : nullptr;
}

/// <summary>
/// Returns an available ID for an object to identify its sprite in the m_spriteMap
/// For objects that aren't assigned filepaths or IDs in the level editors (like TextObjects)
/// </summary>
uint32_t SpriteManager::getNextFreeID()
{
	m_inUseIDs.push_back(0);
	return static_cast<uint32_t>(m_inUseIDs.size());
}

/// <summary>
/// Resets the available IDs back to 0
/// </summary>
void SpriteManager::resetIDs()
{
	m_inUseIDs.clear();
	while (!m_amountIDAtStateStart.empty())
	{
		m_amountIDAtStateStart.pop();
	}
}

/// <summary>
/// Store the current number of IDs in use when a new state is PUSHED into the FSM
/// </summary>
void SpriteManager::storeIDsOnStatePush()
{
	m_amountIDAtStateStart.push(static_cast<int>(m_inUseIDs.size()));
}

/// <summary>
/// When a state is POPPED off the FSM, return back to the number of IDs before that state was pushed on
/// </summary>
void SpriteManager::removeIDsAtStatePop()
{
	if (m_amountIDAtStateStart.empty())
		return;

	m_inUseIDs.resize(m_amountIDAtStateStart.top());
	m_amountIDAtStateStart.pop();
}
