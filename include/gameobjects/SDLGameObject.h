#pragma once
#include "BaseGameObject.h"

#include "utility/GameObjectFactory.h"

// How close an object can get to the edge of the screen
#define edgeScreenBuffer 35

class SDLGameObject :
    public BaseGameObject
{
public:
    SDLGameObject();
	~SDLGameObject();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

    virtual void drawObject();
    virtual void updateObject();

	Vector2D& getPosition();
	int getWidth();
	int getHeight();

protected:

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

	// The dimensions of the object is the dimensions of an individual sprite frame
    int m_objectWidth;	
    int m_objectHeight;	

    int m_currentSpriteFrame;
	int m_framesInSprite; // Amount of separate sprite frames in sprite
	int m_animationSpeed;
	float m_movementSpeed;

	int m_screenWidth;
	int m_screenHeight;

    std::string m_objectTextureID;

	bool m_bFlipImage;
};

class SDLGameObjectCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new SDLGameObject();
	}
};
