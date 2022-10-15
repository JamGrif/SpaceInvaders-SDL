#include "pch.h"
#include "states/BaseState.h"

#include "gameobjects/BaseGameObject.h"
#include "gameobjects/Button.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/TextObject.h"
#include "level/Level.h"
#include "level/LevelParser.h"
#include "level/ObjectLayer.h"

/// <summary>
/// Called when state is removed from game state machine
/// </summary>
bool BaseState::onExitState()
{
	delete m_pStateLevel;

	return true;
}

/// <summary>
/// Update the level used in this state
/// </summary>
void BaseState::updateState()
{
	m_pStateLevel->updateLevel();
}

/// <summary>
/// Draw the level used in this state
/// </summary>
void BaseState::renderState()
{
	m_pStateLevel->renderLevel();
}

/// <summary>
/// Link any callback functions with their respective objects
/// The ID of the callback function itself is set in each state object that derives from BaseState
/// The ID of the function the object uses is set in the level editor
/// This function links the two IDs together allowing an object can call its specified function
/// </summary>
void BaseState::setCallbacks()
{
	// Get the list of game objects
	ObjectLayer& oLayer = dynamic_cast<ObjectLayer&>(*m_pStateLevel->getLayer(LayerIndex::objectLayer)); 
	std::vector<BaseGameObject*>& m_gameObjects = oLayer.getGameObjects();

	// Go through the game objects
	for (auto object : m_gameObjects)
	{
		// If they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<Button*>(object)) // use dynamic_cast to check if the object is a Button type
		{
			// Use the objects callbackID as the index into the callbacks vector and assign the correct function
			Button* pButton = dynamic_cast<Button*>(object);
			pButton->setSelectCallback(m_stateCallbackFunctions.at(pButton->getSelectCallbackID()));

			if (dynamic_cast<CheckboxButton*>(object))
			{
				CheckboxButton* temp = dynamic_cast<CheckboxButton*>(object);
				temp->setCheckboxStateCallback(m_checkBoxStateCallbackFunctions.at(temp->getCheckboxCallbackID()));
			}
		}

		if (dynamic_cast<TextObject*>(object))
		{
			TextObject* text = dynamic_cast<TextObject*>(object);
			if (text->getTextCallbackID() != 0)
			{
				text->setTextCallback(m_textCallbackFunctions.at(text->getTextCallbackID()));
			}
		}
	}
}

/// <summary>
/// Use the LevelParser to load .tmx file at filepath
/// </summary>
void BaseState::loadLevel(const std::string& filepath)
{
	LevelParser levelParser;
	m_pStateLevel = levelParser.parseLevel(filepath);
}
