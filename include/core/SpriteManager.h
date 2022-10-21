#pragma once

// Everything that uses SpriteManager will need access to Sprite too
#include "core/Sprite.h"

/// <summary>
/// Controls creation, usage and destruction of Sprite objects
/// </summary>
class SpriteManager
{
public:
	bool	loadSprite(const std::string& filepath, const std::string& id);

	void	clearAllFromSpriteMap();
	void	clearFromSpriteMap(const std::string& id);

	void	drawSpriteFrame(const std::string& id, int x, int y, int width, int height, int currentFrame, bool flipHorizontal);
	void	drawSpriteTile(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame);
	void	drawSpriteText(SDL_Texture* textObjectTexture, const SDL_Rect& textObjectAttributes);

	std::shared_ptr<Sprite>	getSpriteViaID(const std::string& id) const;

	static SpriteManager* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new SpriteManager();
		return s_pInstance;
	}

private:
	static SpriteManager* s_pInstance;

	std::unordered_map<std::string, std::shared_ptr<Sprite>> m_spriteMap;

	// Number of pixels between the edge of a tileset picture
	const int m_tilesetPixelMargin;

	// Number of pixels between each sprite in a tileset picture
	const int m_tilesetPixelSpacing;
		
	SpriteManager() :m_tilesetPixelMargin(2), m_tilesetPixelSpacing(2) {};						// Prevent outside unwanted construction
	SpriteManager(const SpriteManager&) :m_tilesetPixelMargin(2), m_tilesetPixelSpacing(2) {};	// Prevent construction by copying
	SpriteManager& operator=(const SpriteManager&) {};											// Prevent assignment
	~SpriteManager() {};																		// Prevent outside unwanted destruction
};
typedef SpriteManager TheSpriteManager;
