#include "pch.h"
#include "states/BaseState.h"

#include "core/SoundManager.h"
#include "gameobjects/BaseGameObject.h"
#include "gameobjects/Button.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/TextObject.h"
#include "level/Level.h"
#include "level/LevelParser.h"

/// <summary>
/// Called when state is removed from game state machine
/// </summary>
bool BaseState::onExitState()
{
	delete m_pStateLevel;

	// Stops sounds being played in the wrong state
	TheSoundManager::Instance()->stopAllSounds();

	return true;
}

/// <summary>
/// Update the level used in this state
/// </summary>
void BaseState::updateState()
{
	// Update gameobject vector
	auto it = m_allGameObjects.begin();
	while (it != m_allGameObjects.end())
	{
		if ((*it)->getDestroy())
		{
			it = m_allGameObjects.erase(it);
			continue;
		}
		else
		{
			(*it)->updateObject();
			it++;
		}
	}

	m_pStateLevel->updateLevel();
}

/// <summary>
/// Draw the level used in this state
/// </summary>
void BaseState::renderState()
{
	for (const auto& o : m_allGameObjects)
	{
		// Only draw if object is not going to be destroyed next frame
		if (!o->getDestroy())
			o->drawObject();
	}

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
	// Use the objects callbackID as the index into the callbacks vector and assign the correct function to any required objects
	for (const auto& o : m_allGameObjects)
	{
		// If object is a Button object, set its callback function ID
		auto button = std::dynamic_pointer_cast<Button>(o);
		if (button)
		{
			button->setSelectCallback(m_stateCallbackFunctions.at(button->getSelectCallbackID()));

			// If Button is also a CheckboxButton, sets its checkbox state callback function ID
			auto checkBox = std::dynamic_pointer_cast<CheckboxButton>(o);
			if (checkBox)
			{
				checkBox->setCheckboxStateCallback(m_checkBoxStateCallbackFunctions.at(checkBox->getCheckboxCallbackID()));
			}
		}

		// If object is a TextObject, sets its text callback function ID
		auto textObject = std::dynamic_pointer_cast<TextObject>(o);
		if (textObject && textObject->getTextCallbackID() != 0)
		{
			textObject->setTextCallback(m_textCallbackFunctions.at(textObject->getTextCallbackID()));
		}
	}
}

/// <summary>
/// Use the LevelParser to load .tmx file at filepath
/// </summary>
void BaseState::loadLevel(const std::string& filepath)
{
	LevelParser levelParser;
	m_pStateLevel = levelParser.parseLevel(filepath, m_allGameObjects);
}
