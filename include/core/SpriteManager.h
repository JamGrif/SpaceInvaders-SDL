#pragma once

// Everything that uses SpriteManager will need access to Sprite too
#include "core/Sprite.h"

#include <stack>
#include <list>

/// <summary>
/// Controls creation, usage and destruction of Sprite objects
/// </summary>
class SpriteManager
{
public:
	bool					loadSprite(const std::vector<std::pair<std::string, std::string>>& spritesToLoad);
	bool					loadSprite(const std::string& filepath, const std::string& id);
	bool					loadSprite(SDL_Texture* pCreatedTexture, const std::string& id);

	void					clearAllFromSpriteMap();
	void					clearFromSpriteMap(const std::string& id);

	void					drawSpriteFrame(const std::string& id, const SDL_Rect& objectAttributes, uint8_t currentFrame, bool flipHorizontal, double spriteRotation);
	void					drawSpriteTile(const std::string& id, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t currentRow, uint8_t currentFrame);
	void					drawSpriteText(const std::string& id, const SDL_Rect& objectAttributes);

	std::weak_ptr<Sprite>	getSpriteViaID(const std::string& id) const;

	// This is for gameobjects that use sprites but are not assigned IDs in the level editor or use a filepath (TextObject objects)
	// To identity what sprite each TextObject uses, its ID is based on the size of the m_inUseIDs vector
	// Every time a new state is PUSHED into the state machine, the number of currently used IDs are stored and then when that state is POPPED, the number of currently used IDs returns back to that number
	// CHANGING state will reset the IDs in use back to 0
	// This system means TextObject don't regenerate new Sprite objects every time they are loaded as each object will always use the same ID every time the state is loaded
	std::stack<uint32_t>	m_amountIDAtStateStart;	// The number of IDs being used when a state is pushed into the FSM
	std::list<uint32_t>		m_inUseIDs;					// Number of IDs that are currently being used by an object to identity its sprite in m_spriteMap

	uint32_t				getNextFreeID();
	void					resetIDs();

	void					storeIDsOnStatePush();
	void					removeIDsAtStatePop();

	static SpriteManager*	Instance() // Get instance
	{
		static SpriteManager* s_pInstance = new SpriteManager;
		return s_pInstance;
	}

private:

	std::unordered_map<std::string, std::shared_ptr<Sprite>> m_spriteMap;

	// Number of pixels between the edge of a tileset picture
	const uint8_t			m_tilesetPixelMargin;

	// Number of pixels between each sprite in a tileset picture
	const uint8_t			m_tilesetPixelSpacing;
		
	SpriteManager() :m_tilesetPixelMargin(2), m_tilesetPixelSpacing(2) {};	// Prevent outside unwanted construction
	SpriteManager(const SpriteManager&) = delete;							// Prevent construction by copying
	SpriteManager& operator=(const SpriteManager&) = delete;				// Prevent assignment
	~SpriteManager() {};													// Prevent outside unwanted destruction
};
typedef SpriteManager TheSpriteManager;
