#include "pch.h"
#include "core/SpriteManager.h"

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "core/Renderer.h"

SpriteManager* SpriteManager::s_pInstance = nullptr;


bool SpriteManager::loadSprite(const std::string& fileName, const std::string& id)
{
	// Sprite at filepath already exists
	if (m_spriteMap.count(id))
		return false;
	
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (!pTexture)
		return false;
	
	Sprite* s = new Sprite(pTexture, fileName, id);
	m_spriteMap[id] = s;

	return true;
}

void SpriteManager::clearAllFromSpriteMap()
{
	for (auto& sprite : m_spriteMap)
	{
		delete sprite.second;
	}
	m_spriteMap.clear();
}

/// <summary>
/// Remove the specified texture from the textureMap
/// </summary>
void SpriteManager::clearFromSpriteMap(const std::string& id)
{
	delete m_spriteMap.at(id);
	m_spriteMap.erase(id);
}

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

// Returns sprite at id, nullptr if doesn't exist
Sprite* SpriteManager::getSpriteViaID(const std::string& id) const
{
	return m_spriteMap.count(id) ? m_spriteMap.at(id) : nullptr;
}

