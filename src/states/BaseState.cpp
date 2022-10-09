#include "pch.h"
#include "states/BaseState.h"

#include "level/Level.h"
#include "level/LevelParser.h"
#include "gameobjects/BaseGameObject.h"

#include "gameobjects/Button.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/TextObject.h"
#include "level/ObjectLayer.h"

bool BaseState::onExitState()
{
	delete m_pStateLevel;

	return true;
}

void BaseState::updateState()
{
	m_pStateLevel->updateLevel();
}

void BaseState::renderState()
{
	m_pStateLevel->renderLevel();
}

/// <summary>
/// Link any state MenuButton objects with any states callback functions
/// </summary>
void BaseState::setCallbacks()
{
	//if (m_stateCallbackFunctions.empty())
	//{
	//	std::cout << "m_stateCallbackFunctions is empty" << std::endl;
	//	return;
	//}

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
			//text->setTextCallback(m_textCallbackFunctions.at(text->getTextCallbackID()));
		}
	}
}

void BaseState::loadLevel(const std::string& level)
{
	LevelParser levelParser;
	m_pStateLevel = levelParser.parseLevel(level.c_str());
}
