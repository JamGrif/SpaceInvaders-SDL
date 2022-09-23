#pragma once

#include "SDL.h"
#include <string>
#include <map>

/* SDL_Texture* m_pTexture;	// The image itself */

class TextureManager
{
public:
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawframe(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static TextureManager* Instance(); // Singleton
private:
	TextureManager();
	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};
typedef TextureManager TheTextureManager;
