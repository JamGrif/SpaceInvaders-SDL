#include "pch.h"
#include "core/SpriteManager.h"

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "core/Renderer.h"

SpriteManager* SpriteManager::s_pInstance = nullptr;

SpriteManager::SpriteManager()
{
}

bool SpriteManager::loadSprite(const std::string& fileName, const std::string& id)
{
	// Ensure texture doesn't currently exist
	if (m_spriteMap.find(id) != m_spriteMap.end())
	{
		//std::cout << fileName << " already exists " << std::endl;
		return false;
	}

	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// Texture creation successful, create sprite and add to map
	if (pTexture)
	{
		Sprite* s = new Sprite(pTexture, fileName, id);
		m_spriteMap[id] = s;
		return true;
	}

	// Reaching here means something went wrong
	return false;
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

void SpriteManager::drawSpriteTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;


	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_spriteMap[id]->getTexturePtr(), &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
