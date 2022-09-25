#pragma once


#include <map>

// Forward Declaration
struct SDL_Renderer;
struct SDL_Texture;

/* SDL_Texture* m_pTexture;	// The image itself */

class TextureManager
{
public:
	bool load(std::string fileName, std::string id);
	void clearFromTextureMap(std::string id);

	void draw(std::string id, int x, int y, int width, int height, bool flipHorizontal);
	void drawframe(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, bool flipHorizontal);

	static TextureManager* Instance(); // Singleton
private:
	TextureManager();
	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};
typedef TextureManager TheTextureManager;
