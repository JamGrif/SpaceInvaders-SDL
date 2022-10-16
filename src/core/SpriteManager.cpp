#include "pch.h"
#include "core/SpriteManager.h"

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "core/Renderer.h"

SpriteManager* SpriteManager::s_pInstance = nullptr;

/// <summary>
/// Create sprite at filepath and assign an id to it
/// </summary>
bool SpriteManager::loadSprite(const std::string& filepath, const std::string& id)
{
	// Sprite at filepath already exists
	if (m_spriteMap.count(id))
		return false;
	
	SDL_Surface* pTempSurface = IMG_Load(filepath.c_str());
	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (!pTexture)
		return false;
	
	Sprite* pSprite = new Sprite(pTexture, filepath, id);
	m_spriteMap[id] = pSprite;

	return true;
}

/// <summary>
/// Delete all loaded sprite objects from the spriteMap
/// </summary>
void SpriteManager::clearAllFromSpriteMap()
{
	//std::cout << "start of clearallsprites" << std::endl;
	for (const auto& [key, value] : m_spriteMap)
	{
		delete value;
	}
	m_spriteMap.clear();
	//std::cout << "end of clearallsprites" << std::endl;
}

/// <summary>
/// Delete the specified loaded sprite object from the spriteMap
/// </summary>
void SpriteManager::clearFromSpriteMap(const std::string& id)
{
	delete m_spriteMap.at(id);
	m_spriteMap.erase(id);
}

/// <summary>
/// Draw the specified sprite, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteFrame(const std::string& id, int x, int y, int width, int height, int currentFrame, bool flipHorizontal)
{
	SDL_Rect frameToDraw;	// What part of the sprite to use
	SDL_Rect destRect;		// Where on the screen to draw sprite

	frameToDraw.x = width * currentFrame;
	frameToDraw.y = 0;
	frameToDraw.w = width;
	frameToDraw.h = height;

	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RendererFlip flag = flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), &frameToDraw, &destRect, 0, 0, flag);
}

/// <summary>
/// Draw the specified tileset tile, using its id to choose it
/// </summary>
void SpriteManager::drawSpriteTile(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = m_tilesetPixelMargin + (m_tilesetPixelSpacing + width) * currentFrame;
	srcRect.y = m_tilesetPixelMargin + (m_tilesetPixelSpacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

/// <summary>
/// Return sprite object at id, nullptr if doesn't exist
/// </summary>
Sprite* SpriteManager::getSpriteViaID(const std::string& id) const
{
	return m_spriteMap.count(id) ? m_spriteMap.at(id) : nullptr;
}
