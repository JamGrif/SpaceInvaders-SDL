#pragma once

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;

constexpr uint8_t SPRITE_PIXEL_MARGIN  = 2;		// Pixel margin around the sprite sheet
constexpr uint8_t SPRITE_PIXEL_SPACING = 2;		// Pixel space between each frame on the sprite sheet

constexpr uint8_t TILESET_PIXEL_MARGIN  = 2;	// Pixel margin around the tileset
constexpr uint8_t TILESET_PIXEL_SPACING = 2;	// Pixel space between each frame on the tileset

/// <summary>
/// Sets when the texture is created and destroyed
/// </summary>
enum class SpriteType
{
	UNSET_SPRITE = 0,	// Sprite type has not been set
	CORE_SPRITE  = 1,	// Sprite is created outside of any states and deleted on program exit
	STATE_SPRITE = 2	// Sprite is created on State enter and deleted on State exit
};

typedef std::string spriteID;

/// <summary>
/// Encapsulates a SDL_Texture object and provides utility functions for it
/// Created and destroyed by SpriteManager
/// </summary>
class Sprite
{
public:
	Sprite();
	~Sprite();

	bool						loadSprite(const std::string& filepath, const std::string& id, SpriteType spriteType);
	bool						loadSprite(SDL_Texture* pCreatedTexture, const spriteID& id, SpriteType spriteType);

	void						setUpIndividualSpriteDimensions(int numFrames, int numRows);
	void						calculateSpriteDimensions();

	SDL_Surface*				getSurfacePtr() { return m_pSurfaceObject; }
	SDL_Texture*				getTexturePtr() { return m_pTextureObject; }
	std::string&				getFilepath() { return m_filepath; }
	std::string&				getID() { return m_id; }
	SpriteType					getSpriteType() { return m_spriteType; }

	std::unique_ptr<SDL_Rect>&	getTotalDimensions() { return m_pTotalSpriteDimensions; };
	std::unique_ptr<SDL_Rect>&	getIndividualDimensions() { return m_pIndivdualSpriteDimension; }

	void						getSpriteDimensions(SDL_Rect& rect);

	void						changeTexture(SDL_Texture* pNewTexture);

	void						setScaleX(float scale) { m_scale.setX(scale); }
	void						setScaleY(float scale) { m_scale.setY(scale); }

	float						getScaleX() { return m_scale.getX(); }
	float						getScaleY() { return m_scale.getY(); }

private:
	SDL_Surface*				m_pSurfaceObject;
	SDL_Texture*				m_pTextureObject;

	std::string					m_filepath;
	std::string					m_id;

	SpriteType					m_spriteType;

	bool						m_bSpriteSetup;

	std::unique_ptr<SDL_Rect>	m_pIndivdualSpriteDimension;
	std::unique_ptr<SDL_Rect>	m_pTotalSpriteDimensions;

	Vector2D					m_scale;
};
