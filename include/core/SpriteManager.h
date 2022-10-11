#pragma once

// Everything that uses SpriteManager will need access to Sprite too
#include "core/Sprite.h"

class SpriteManager
{
public:
	bool loadSprite(const std::string& fileName, const std::string& id);

	void clearAllFromSpriteMap();
	void clearFromSpriteMap(const std::string& id);

	void drawSpriteFrame(const std::string& id, int x, int y, int width, int height, int currentFrame, bool flipHorizontal);
	void drawSpriteTile(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame);

	int m_tilesetPixelMargin = 2;	// Number of pixels between the edge of a tileset picture
	int m_tilesetPixelSpacing = 2;	// Number of pixels between each sprite in a tileset picture

	//int m_spritePixelMargin = 2;	// Number of pixels between the edge of the sprite sheet
	//int m_spritePixelSpacing = 2;	// Number of pixels between each sprite in a sprite sheet


	Sprite* getSpriteViaID(const std::string& id) const;

	static SpriteManager* Instance() // Singleton
	{
		if (!s_pInstance)
			s_pInstance = new SpriteManager();
		return s_pInstance;
	}

private:
	SpriteManager() {};
	SpriteManager(const SpriteManager&) {};
	SpriteManager& operator=(const SpriteManager&) {};
	static SpriteManager* s_pInstance;

	std::unordered_map<std::string, Sprite*> m_spriteMap;
};
typedef SpriteManager TheSpriteManager;
