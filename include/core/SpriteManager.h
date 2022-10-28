#pragma once

// Everything that uses SpriteManager will need access to Sprite too
#include "core/Sprite.h"

/// <summary>
/// Controls creation, usage and destruction of Sprite objects
/// </summary>
class SpriteManager
{
public:
	bool					createSprite(const std::vector<std::pair<std::string, spriteID>>& spritesToLoad, SpriteType spriteType);
	bool					createSprite(const std::string& filepath, const spriteID& id, SpriteType spriteType);
	bool					createSprite(SDL_Texture* pCreatedTexture, const spriteID& id, SpriteType spriteType);

	void					clearAllFromSpriteMap(SpriteType spritetype);

	void					drawSpriteFrame(const spriteID& id, const SDL_Rect& objectAttributes, uint8_t currentRow, uint8_t currentFrame, bool flipHorizontal, double spriteRotation);
	void					drawSpriteTile(const spriteID& id, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t currentRow, uint8_t currentFrame);
	void					drawSpriteText(const spriteID& id, const SDL_Rect& objectAttributes);

	std::weak_ptr<Sprite>	getSpriteViaID(const spriteID& id) const;

	// This is for gameobjects that use sprites but are not assigned IDs in the level editor or use a filepath (such as TextObject objects)
	// To identity what sprite each TextObject uses its given the next increment of the m_inUseIDs variable
	// Every time a new state is PUSHED into the state machine, the number of currently used IDs are stored and then when that state is POPPED, the number of currently used IDs returns back to that number
	// CHANGING state will reset the IDs in use back to NO_IDS (0)
	// This system means TextObject don't regenerate new Sprite objects every time they are loaded as each object will always use the same ID every time the state is loaded
	uint32_t				getNextFreeID();
	void					storeIDsOnStatePush();
	void					removeIDsAtStatePop();

	static SpriteManager*	Instance() // Get instance
	{
		static SpriteManager* s_pInstance = new SpriteManager;
		return s_pInstance;
	}

private:

	std::unordered_map<spriteID, std::shared_ptr<Sprite>> m_spriteMap;

	// The number of IDs being used when a state is pushed into the FSM
	std::stack<uint32_t>	m_amountIDAtStateStart;

	// Number of IDs that are currently being used by an object to identity its sprite in m_spriteMap
	uint32_t				m_inUseIDs;

	void					resetIDs();
		
	SpriteManager();											// Prevent outside unwanted construction
	~SpriteManager();											// Prevent outside unwanted destruction
	SpriteManager(const SpriteManager&) = delete;				// Prevent construction by copying
	SpriteManager& operator=(const SpriteManager&) = delete;	// Prevent assignment
};
typedef SpriteManager TheSpriteManager;
