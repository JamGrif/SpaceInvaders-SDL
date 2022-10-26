#pragma once

struct SDL_Texture;
struct SDL_Rect;

constexpr uint8_t SPRITE_PIXEL_MARGIN = 2;	// Pixel margin around the sprite sheet
constexpr uint8_t SPRITE_PIXEL_SPACING = 2; // Pixel space between each frame on the sprite sheet

/// <summary>
/// Encapsulates a SDL_Texture object and provides utility functions for it
/// Created and destroyed by SpriteManager
/// </summary>
class Sprite
{
public:
	Sprite(SDL_Texture* texture, const std::string& fileName, const std::string& id);
	~Sprite();

	void						setUpIndividualSpriteDimensions(int numFrames);
	void						calculateSpriteDimensions();

	SDL_Texture*				getTexturePtr() { return m_textureObject; }
	std::string&				getFileName() { return m_fileName; }
	std::string&				getID() { return m_id; }

	std::unique_ptr<SDL_Rect>&	getTotalDimensions() { return m_totalSpriteDimensions; };
	std::unique_ptr<SDL_Rect>&	getIndividualDimensions() { return m_indivdualSpriteDimension; }

	void						getSpriteDimensions(SDL_Rect& rect);

	void						changeTexture(SDL_Texture* pNewTexture);

private:
	SDL_Texture*				m_textureObject;

	std::string					m_fileName;
	std::string					m_id;

	std::unique_ptr<SDL_Rect>	m_indivdualSpriteDimension;
	std::unique_ptr<SDL_Rect>	m_totalSpriteDimensions;

	bool						m_bSpriteSetup;
};
