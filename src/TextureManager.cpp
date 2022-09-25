#include "TextureManager.h"

#include "SDL_image.h"

#include <iostream>

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager* TextureManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}

	return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// Texture creation successful, add to map
	if (pTexture)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	// Reaching here means something went wrong
	return false;
}

/// <summary>
/// Remove the specified texture from the textureMap
/// </summary>
/// <param name="id"></param>
void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
{
	SDL_Rect srcRect;	// What part of the texture to use
	SDL_Rect destRect;	// Where on the screen/window to draw it

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawframe(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
{
	SDL_Rect srcRect;	// What part of the texture to use
	SDL_Rect destRect;	// Where on the screen/window to draw it

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
