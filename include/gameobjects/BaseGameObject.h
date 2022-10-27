#pragma once

/// <summary>
/// Passed to BaseGameObjects through their load function to setup initial values of an object
/// Mainly used to retrieve values from the level data file to create objects in LevelParser
/// </summary>
class LoaderParams
{
public:
	LoaderParams()
		:xPos(0), yPos(0), numRows(1), defaultRow(0), numFrames(1), movementSpeed(0.0f), animationSpeed(0), scoreWorth(0), selectCallbackID(0),
		checkboxStateCallbackID(0), livesRequired(0), textCallbackID(0), textSize(10) {}
	~LoaderParams(){}

	int32_t xPos;						// Starting X position
	int32_t yPos;						// Starting Y position
	std::string classType;				// Class type of object

	std::string textureID;				// Texture the object uses by default
	int32_t	numRows;					// Number of separate rows in sprite sheet (default is sprite has one row)
	int32_t defaultRow;					// Which row to set as default and starting row (default is first row)
	int32_t numFrames;					// Number of separate frames in sprite sheet (default is sprite has one frame)
	float movementSpeed;				// Speed at which the object moves
	int32_t animationSpeed;				// Time until next sprite frame change (_ms means milliseconds) (default is sprite frame will not change)

	int32_t scoreWorth;					// Used in Alien - How much the alien increases the current score by when killed
	int32_t selectCallbackID;			// Used in Button - The ID of the function it will call when clicked on
	int32_t checkboxStateCallbackID;	// Used in CheckboxButton - Finds the starting state of the checkbox (filled or not)
	int32_t livesRequired;				// Used in PlayerLives
	std::string text;					// Used in TextObject - The actual text it will display (assuming its not using a textCallback function)
	int32_t textCallbackID;				// Used in TextObject - Lets a text object copy a variable value
	int32_t textSize;					// Used in TextObject - Sets the size of the font
};

/// <summary>
/// Enforces an interface for all SDLGameObject objects
/// </summary>
class BaseGameObject
{
public:
	BaseGameObject() :m_bDestroy(false) { /*std::cout << "created gameobject" << std::endl;*/ }
	virtual ~BaseGameObject() { /*std::cout << m_classType << " object has been destroyed" << std::endl;*/ }

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams) = 0;

	virtual void	drawObject() = 0;
	virtual void	updateObject() = 0;

	bool			getDestroy() { return m_bDestroy; }

	std::string		getClassType() { return m_classType; }

protected:
	bool			m_bDestroy;
	std::string		m_classType;
};

