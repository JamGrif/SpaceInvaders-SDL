#pragma once

#include "SDL2/SDL.h"

/* SDL_Texture* m_pTexture;	// The image itself */

struct Sprite
{
	Sprite(SDL_Texture* texture, const std::string& fileName, const std::string& id)
		:m_texture(texture), m_fileName(fileName), m_id(id), m_indivdualSpriteDimension{0,0,0,0}
	{
		SDL_QueryTexture(m_texture, NULL, NULL, &m_totalSpriteDimensions.w, &m_totalSpriteDimensions.h);
	}
	~Sprite()
	{
		SDL_DestroyTexture(m_texture);
	}

	// Determine how many sprite frames are in the sprite sheet
	void setUpIndividualSpriteDimensions(int numFrames)
	{
		m_indivdualSpriteDimension.w = m_totalSpriteDimensions.w / numFrames;
		m_indivdualSpriteDimension.h = m_totalSpriteDimensions.h;
	}

	inline SDL_Texture* getTexturePtr() { return m_texture; }
	inline std::string& getFileName() { return m_fileName; }
	inline std::string& getID() { return m_id; }

	inline SDL_Rect& getTotalDimensions() { return m_totalSpriteDimensions; }
	inline SDL_Rect& getIndividualDimensions() { return m_indivdualSpriteDimension; }

private:

	SDL_Texture* m_texture;
	std::string m_fileName;
	std::string m_id;

	SDL_Rect m_indivdualSpriteDimension;
	SDL_Rect m_totalSpriteDimensions;
};

class SpriteManager
{
public:
	bool loadSprite(const std::string& fileName, const std::string& id);

	void clearAllFromSpriteMap();
	void clearFromSpriteMap(const std::string& id);

	void drawSpriteFrame(const std::string& id, int x, int y, int width, int height, int currentFrame, bool flipHorizontal);
	void drawSpriteTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);


	Sprite* getSpriteViaID(const std::string& id) const { return m_spriteMap.at(id); }

	static SpriteManager* Instance() // Singleton
	{
		if (!s_pInstance)
			s_pInstance = new SpriteManager();
		return s_pInstance;
	}

private:
	SpriteManager();
	static SpriteManager* s_pInstance;

	std::unordered_map<std::string, Sprite*> m_spriteMap;
};
typedef SpriteManager TheSpriteManager;
