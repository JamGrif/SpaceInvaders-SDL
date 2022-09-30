#include "pch.h"
#include "core/TextureManager.h"

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "core/Renderer.h"

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager* TextureManager::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}

	return s_pInstance;
}

bool TextureManager::load(const std::string& fileName, const std::string& id)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), pTempSurface);
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
void TextureManager::clearFromTextureMap(const std::string& id)
{
	m_textureMap.erase(id);
}

void TextureManager::draw(const std::string& id, int x, int y, int width, int height, bool flipHorizontal)
{
	SDL_Rect srcRect;	// What part of the texture to use
	SDL_Rect destRect;	// Where on the screen/window to draw it

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RendererFlip temp = flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_textureMap[id], &srcRect, &destRect, 0, 0, temp);
}

void TextureManager::drawframe(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame, bool flipHorizontal)
{
	SDL_Rect srcRect;	// What part of the texture to use
	SDL_Rect destRect;	// Where on the screen/window to draw it

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RendererFlip temp = flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_textureMap[id], &srcRect, &destRect, 0, 0, temp);
}

void TextureManager::drawTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(TheRenderer::Instance()->getRendererPtr(), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
