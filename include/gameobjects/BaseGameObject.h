#pragma once

/// <summary>
/// Passed to BaseGameObjects through their load function to setup initial values of an object
/// Mainly used to retrieve values from the level data file to create objects
/// </summary>
class LoaderParams
{
public:
	LoaderParams()
		:xPos(0), yPos(0), numFrames(1), movementSpeed(0.0f), animationSpeed(0), scoreWorth(0), selectCallbackID(0),
		checkboxStateCallbackID(0), livesRequired(0), textCallbackID(0), textSize(10) {}
	~LoaderParams(){}

	int xPos;						// Starting X position
	int yPos;						// Starting Y position
	std::string classType;			// Class type of object

	std::string textureID;			// Texture the object uses by default
	int numFrames;					// Number of separate frames in sprite (default is sprite has one frame)
	float movementSpeed;			// Speed at which the object moves

	int animationSpeed;				// Time until next sprite frame change (_ms means milliseconds) (default is sprite frame will not change)

	int scoreWorth;					// Used in Alien - How much the alien increases the current score by when killed
	int selectCallbackID;			// Used in Button - The ID of the function it will call when clicked on
	int checkboxStateCallbackID;	// Used in CheckboxButton - Finds the starting state of the checkbox (filled or not)
	int livesRequired;				// Used in PlayerLives
	std::string text;				// Used in TextObject - The actual text it will display (assuming its not using a textCallback function)
	int textCallbackID;				// Used in TextObject - Lets a text object copy a variable value
	int textSize;					// Used in TextObject - Sets the size of the font
};

/// <summary>
/// Enforces an interface for all SDLGameObject objects
/// </summary>
class BaseGameObject
{
public:
	BaseGameObject() :m_bDestroy(false) { /*std::cout << "created gameobject" << std::endl;*/ }
	virtual ~BaseGameObject() { /*std::cout << m_classType << " object has been destroyed" << std::endl;*/ }

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams) = 0;

	virtual void drawObject() = 0;
	virtual void updateObject() = 0;

	bool getDestroy() { return m_bDestroy; }

	std::string getClassType() { return m_classType; }

protected:
	bool m_bDestroy;
	std::string m_classType;
};

