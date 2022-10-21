#include "pch.h"
#include "states/BaseState.h"

#include "core/SoundManager.h"
#include "gameobjects/BaseGameObject.h"
//#include "gameobjects/Block.h"
//#include "gameobjects/Alien.h"
#include "gameobjects/Button.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/TextObject.h"
#include "level/Level.h"
#include "level/LevelParser.h"
//#include "level/ObjectLayer.h"

/// <summary>
/// Called when state is removed from game state machine
/// </summary>
bool BaseState::onExitState()
{
	delete m_pStateLevel;

	for (const auto& o : m_allGameObjects)
	{
		//std::cout << o->getClassType() << " used this many times : " << o.use_count() << std::endl;
	}
	//m_allGameObjects.clear();

	// Stops sounds being played in the wrong state
	TheSoundManager::Instance()->stopAllSounds();

	return true;
}

/// <summary>
/// Update the level used in this state
/// </summary>
void BaseState::updateState()
{
	for (int i = 0; i < m_allGameObjects.size(); i++)
	{
		if (m_allGameObjects.at(i)->getDestroy())
		{
			m_allGameObjects.erase(m_allGameObjects.begin() + i);
		}
		else
		{
			m_allGameObjects.at(i)->updateObject();
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
	// Go through the game objects
	for (const auto& o : m_allGameObjects)
	{
		// If they are of type MenuButton then assign a callback based on the id passed in from the file
		if (std::dynamic_pointer_cast<Button>(o))
		{
			// Use the objects callbackID as the index into the callbacks vector and assign the correct function
			std::shared_ptr<Button> pButton = std::dynamic_pointer_cast<Button>(o);
			pButton->setSelectCallback(m_stateCallbackFunctions.at(pButton->getSelectCallbackID()));

			if (std::dynamic_pointer_cast<CheckboxButton>(o))
			{
				std::shared_ptr<CheckboxButton> temp = std::dynamic_pointer_cast<CheckboxButton>(o);
				temp->setCheckboxStateCallback(m_checkBoxStateCallbackFunctions.at(temp->getCheckboxCallbackID()));
			}
		}

		if (std::dynamic_pointer_cast<TextObject>(o))
		{
			std::shared_ptr<TextObject> text = std::dynamic_pointer_cast<TextObject>(o);
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
	m_pStateLevel = levelParser.parseLevel(filepath, m_allGameObjects);
}
