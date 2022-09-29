#pragma once


// Forward Declaration
struct SDL_Renderer;
struct SDL_Texture;

/* SDL_Texture* m_pTexture;	// The image itself */

class TextureManager
{
public:
	bool load(const std::string& fileName, const std::string& id);
	void clearFromTextureMap(const std::string& id);

	void draw(const std::string& id, int x, int y, int width, int height, bool flipHorizontal);
	void drawframe(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame, bool flipHorizontal);
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);

	static TextureManager* Instance(); // Singleton
private:
	TextureManager();
	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};
typedef TextureManager TheTextureManager;
