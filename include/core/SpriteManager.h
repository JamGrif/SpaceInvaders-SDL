#pragma once

// Everything that uses SpriteManager will need access to Sprite too
#include "core/Sprite.h"

/// <summary>
/// Controls creation, usage and destruction of Sprite objects
/// </summary>
class SpriteManager
{
public:
	bool	loadSprite(const std::vector<std::pair<std::string, std::string>>& spritesToLoad);
	bool	loadSprite(const std::string& filepath, const std::string& id);

	void	clearAllFromSpriteMap();
	void	clearFromSpriteMap(const std::string& id);

	void	drawSpriteFrame(const std::string& id, const SDL_Rect& objectAttributes, uint8_t currentFrame, bool flipHorizontal, double spriteRotation);
	void	drawSpriteTile(const std::string& id, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t currentRow, uint8_t currentFrame);
	void	drawSpriteText(SDL_Texture* textObjectTexture, const SDL_Rect& textObjectAttributes);

	std::shared_ptr<Sprite>	getSpriteViaID(const std::string& id) const;

	static SpriteManager* Instance() // Get instance
	{
		static SpriteManager* s_pInstance = new SpriteManager;
		return s_pInstance;
	}

private:

	std::unordered_map<std::string, std::shared_ptr<Sprite>> m_spriteMap;

	// Number of pixels between the edge of a tileset picture
	const uint8_t m_tilesetPixelMargin;

	// Number of pixels between each sprite in a tileset picture
	const uint8_t m_tilesetPixelSpacing;
		
	SpriteManager() :m_tilesetPixelMargin(2), m_tilesetPixelSpacing(2) {};	// Prevent outside unwanted construction
	SpriteManager(const SpriteManager&) = delete;							// Prevent construction by copying
	SpriteManager& operator=(const SpriteManager&) = delete;				// Prevent assignment
	~SpriteManager() {};													// Prevent outside unwanted destruction
};
typedef SpriteManager TheSpriteManager;
