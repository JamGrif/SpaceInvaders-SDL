#pragma once
#include "gameobjects/BaseGameObject.h"

#include "gameobjects/utility/GameObjectFactory.h"

// How close an object can get to the edge of the screen before something happens
#define EDGE_SCREEN_BUFFER 40

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

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

    virtual void drawObject();
    virtual void updateObject();

	Vector2D& getPosition() { return m_position; }

	int getWidth() const { return m_objectWidth; }
	int getHeight() const { return m_objectHeight; };

protected:
    Vector2D m_position;
    Vector2D m_velocity;

	// The dimensions of the object is the dimensions of an individual sprite frame
    int m_objectWidth;	
    int m_objectHeight;	

	// Current sprite frame in use of loaded sprite
    int m_currentSpriteFrame;

	// Total amount of separate sprite frames of loaded sprite
	int m_framesInSprite;

	// Time until next sprite frame change (_ms means milliseconds)
	int m_animationSpeed_ms;

	float m_movementSpeed;

	// Dimensions of game window
	int m_screenWidth;
	int m_screenHeight;

	// ID of sprite this object uses
    std::string m_objectTextureID;

	// Flip sprite on draw?
	bool m_bFlipImage;
};

/// <summary>
/// Registers an object with the GameObjectFactory which is used to create objects from the level editor files (.tmx)
/// Only required for objects that are spawned from the level editor
/// Any new inherited game objects must also inherit and implement this class 
/// </summary>
class SDLGameObjectCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new SDLGameObject();
	}
};
