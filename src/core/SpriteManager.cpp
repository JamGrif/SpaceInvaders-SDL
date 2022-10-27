#include "pch.h"
#include "core/SpriteManager.h"

#include "SDL2/SDL.h"

#include "core/Renderer.h"

static constexpr uint32_t NO_IDS = 0;

/// <summary>
/// Create sprite at filepath of type spriteType and assign an id to it
/// </summary>
bool SpriteManager::createSprite(const std::string& filepath, const spriteID& id, SpriteType spriteType)
{
	// Check if sprite at filepath already exists
	if (m_spriteMap.find(id) != m_spriteMap.end())
		return false;

	std::shared_ptr<Sprite> pSprite = std::make_shared<Sprite>();
	if (pSprite->loadSprite(filepath, id, spriteType))
	{
		m_spriteMap.insert({ id, pSprite });
	}

	return true;
}

/// <summary>
/// Load a collection of sprites using the filepath and id from the pair structure
/// </summary>
bool SpriteManager::createSprite(const std::vector<std::pair<std::string, spriteID>>& spritesToLoad, SpriteType spriteType)
{
	// Loop through and load each sprite using its filepath(first) and id(second) and spriteType
	for (const auto& s : spritesToLoad)
	{
		createSprite(s.first, s.second, spriteType);
	}

	return true;
}

/// <summary>
/// Create a Sprite object from an already created SDL_Texture and assign an id and spriteType to it
/// </summary>
bool SpriteManager::createSprite(SDL_Texture* pCreatedTexture, const spriteID& id, SpriteType spriteType)
{
	// Check if sprite with id already exists
	if (m_spriteMap.find(id) != m_spriteMap.end())
		return false;

	std::shared_ptr<Sprite> pSprite = std::make_shared<Sprite>();
	if (pSprite->loadSprite(pCreatedTexture, id, spriteType))
	{
		m_spriteMap.insert({ id, pSprite });
	}

	return true;
}

/// <summary>
/// Delete all loaded sprite objects from the spriteMap
/// </summary>
void SpriteManager::clearAllFromSpriteMap(SpriteType spritetype)
{
	auto it = m_spriteMap.begin();
	while (it != m_spriteMap.end())
	{
		if ((*it).second->getSpriteType() == spritetype)
		{
			it = m_spriteMap.erase(it);
		}
		else
		{
			it++;
		}
	}

	// As all sprites have been removed, clear free IDs
	if (spritetype == SpriteType::STATE_SPRITE)
	{
		resetIDs();
	}
	
}

/// <summary>
/// Draw the specified sprite, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteFrame(const spriteID& id, const SDL_Rect& objectAttributes, uint8_t currentRow, uint8_t currentFrame, bool flipHorizontal, double spriteRotation)
{
	if (m_spriteMap.find(id) == m_spriteMap.end())
	{
		std::cout << "sprite with id: " << id << " doesn't exist" << std::endl;
		return;
	}

	SDL_Rect spriteFrame; // What part of the sprite sheet to use

	spriteFrame.x = ((objectAttributes.w * currentFrame) + SPRITE_PIXEL_MARGIN) + currentFrame * SPRITE_PIXEL_SPACING;
	spriteFrame.y = ((objectAttributes.h * currentRow) + SPRITE_PIXEL_MARGIN) + currentRow * SPRITE_PIXEL_SPACING;
	spriteFrame.w = objectAttributes.w;
	spriteFrame.h = objectAttributes.h;

	SDL_Rect rect = objectAttributes;
	rect.w *= m_spriteMap[id]->getScaleX();
	rect.h *= m_spriteMap[id]->getScaleY();

	SDL_RendererFlip flag = flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), &spriteFrame, &rect, spriteRotation, 0, flag);
}

/// <summary>
/// Draw the specified tileset tile, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteTile(const spriteID& id, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t currentRow, uint8_t currentFrame)
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
void SpriteManager::drawSpriteText(const spriteID& id, const SDL_Rect& objectAttributes)
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
std::weak_ptr<Sprite> SpriteManager::getSpriteViaID(const spriteID& id) const
{
	return m_spriteMap.find(id) != m_spriteMap.end() ? m_spriteMap.at(id) : nullptr;
}

/// <summary>
/// Returns an available ID for an object to identify its sprite in the m_spriteMap
/// For objects that aren't assigned filepaths or IDs in the level editors (like TextObjects)
/// </summary>
uint32_t SpriteManager::getNextFreeID()
{
	return ++m_inUseIDs;
}

/// <summary>
/// Resets the available IDs back to 0
/// </summary>
void SpriteManager::resetIDs()
{
	m_inUseIDs = NO_IDS;
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
	m_amountIDAtStateStart.push(m_inUseIDs);
}

/// <summary>
/// When a state is POPPED off the FSM, return back to the number of IDs before that state was pushed on
/// </summary>
void SpriteManager::removeIDsAtStatePop()
{
	if (m_amountIDAtStateStart.empty())
		return;

	m_inUseIDs = m_amountIDAtStateStart.top();
	m_amountIDAtStateStart.pop();
}

SpriteManager::SpriteManager()
	:m_inUseIDs(NO_IDS), m_tilesetPixelMargin(TILESET_PIXEL_MARGIN), m_tilesetPixelSpacing(TILESET_PIXEL_SPACING)
{
}

SpriteManager::~SpriteManager()
{
}
