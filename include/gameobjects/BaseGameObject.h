#pragma once

/// <summary>
/// Passed to BaseGameObjects through their load function to setup initial values of an object
/// Mainly used to retrieve values from the level data file to create objects
/// </summary>
class LoaderParams
{
public:
	LoaderParams()
		:xPos(0), yPos(0), numFrames(1), movementSpeed(0.0f), animationSpeed(1), scoreWorth(0), selectCallbackID(0),
		checkboxStateCallbackID(0), livesRequired(0), textCallbackID(0), textSize(10) {}
	~LoaderParams(){}

	int xPos;						// Starting X position
	int yPos;						// Starting Y position

	std::string textureID;			// Texture the object uses by default
	int numFrames;					// Number of separate frames in sprite
	float movementSpeed;			// Speed at which the object moves

	int animationSpeed;				// Used with sprites with more than one frame

	int scoreWorth;					// Used in Alien - How much the alien increases the current score by
	int selectCallbackID;			// Used in Button (MenuButton | CheckboxButton)
	int checkboxStateCallbackID;	// Used in CheckboxButton
	int livesRequired;				// Used in PlayerLives
	std::string text;				// Used in TextObject
	int textCallbackID;				// Used in TextObject - Lets a text object copy a variable value
	int textSize;					// Used in TextObject - Sets the size of the font
};

/// <summary>
/// Enforces an interface for all SDLGameObject objects
/// </summary>
class BaseGameObject
{
public:
	BaseGameObject() {}
	virtual ~BaseGameObject() {}

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams) = 0;

	virtual void drawObject() = 0;
	virtual void updateObject() = 0;
};

