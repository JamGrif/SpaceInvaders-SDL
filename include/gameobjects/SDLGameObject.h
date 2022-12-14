#pragma once
#include "gameobjects/BaseGameObject.h"

#include "SDL2/SDL_rect.h"

#include "gameobjects/utility/GameObjectFactory.h"

// How close an object can get to the edge of the screen before something happens
constexpr uint8_t EDGE_SCREEN_BUFFER = 40;

/// <summary>
/// Basic game object
/// ALL game objects that can appear in the game inherit or use this class
/// </summary>
class SDLGameObject :
    public BaseGameObject
{
public:
    SDLGameObject();
	~SDLGameObject();

	virtual void loadObject(std::unique_ptr<LoaderParams> pParams) override;

    virtual void drawObject() override;
    virtual void updateObject() override;

	const Vector2D&	getPosition() const { return m_position; }

	int32_t		getWidth() const { return m_objectWidth; }
	int32_t		getHeight() const { return m_objectHeight; };

protected:
    Vector2D	m_position;
    Vector2D	m_velocity;

	// The dimensions of the object is the dimensions of an individual sprite frame
	int32_t		m_objectWidth;
	int32_t		m_objectHeight;

	// Sent to the SpriteManager to be used for drawing, values set every draw call.
	// Uses the objects xPos, yYos, width and height
	SDL_Rect	m_objectAttributes;

	// Which row in the sprite sheet to use
	uint8_t		m_currentSpriteRow;

	// Current sprite frame in use of loaded sprite
	uint8_t		m_currentSpriteFrame;

	// Total amount of separate sprite frames of loaded sprite
	uint8_t		m_rowsInSprite;
	uint8_t		m_framesInSprite;

	// Default/starting row to use in sprite
	uint8_t		m_defaultRow;

	// Time until next sprite frame change (_ms means milliseconds)
	uint16_t	m_animationSpeed_ms;

	float		m_movementSpeed;

	// Dimensions of game window
	uint16_t	m_screenWidth;
	uint16_t	m_screenHeight;

	// ID of sprite this object uses
    std::string m_objectTextureID;

	// Flip sprite on draw?
	bool		m_bFlipImage;

	// Rotation of the sprite during drawing (default - 0)
	double		m_spriteRotation;
};

class SDLGameObjectCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<SDLGameObject>();
	}
};
