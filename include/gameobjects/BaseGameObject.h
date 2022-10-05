#pragma once

class LoaderParams
{
public:
	LoaderParams()
		:x(0), y(0), numFrames(1), animationSpeed(1), callbackID(0), movementSpeed(0.0f) {}
	~LoaderParams(){}

	int x;
	int y;

	int numFrames;		// Number of separate frames in sprite
	int animationSpeed; // Used with sprites with more than one frame
	int callbackID;		// Used in MenuButton
	float movementSpeed;  

	std::string textureID;
};

/// <summary>
/// Enforces an interface for all SDLGameObject objects
/// </summary>
class BaseGameObject
{
public:
	BaseGameObject()
	{
	}
	virtual ~BaseGameObject()
	{
	};

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams) = 0;

	virtual void drawObject() = 0;
	virtual void updateObject() = 0;
};

