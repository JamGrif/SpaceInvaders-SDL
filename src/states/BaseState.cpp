#include "pch.h"
#include "states/BaseState.h"

#include "level/Level.h"
#include "level/LevelParser.h"
#include "gameobjects/BaseGameObject.h"

#include "gameobjects/MenuButton.h"
#include "level/ObjectLayer.h"

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
	if (m_stateCallbackFunctions.empty())
	{
		std::cout << "m_stateCallbackFunctions is empty" << std::endl;
		return;
	}

	// Get the list of game objects
	ObjectLayer& test = dynamic_cast<ObjectLayer&>(*m_pStateLevel->getLayer(LayerIndex::objectLayer)); 
	std::vector<BaseGameObject*>& m_gameObjects = test.getGameObjects();

	// Go through the game objects
	for (auto object : m_gameObjects)
	{
		// If they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<MenuButton*>(object)) // use dynamic_cast to check if the object is a MenuButton type
		{
			// Use the objects callbackID as the index into the callbacks vector and assign the correct function
			MenuButton* pButton = dynamic_cast<MenuButton*>(object);
			pButton->setCallback(m_stateCallbackFunctions[pButton->getCallbackID()]);
		}
	}
}

void BaseState::loadLevel(const std::string& level)
{
	LevelParser levelParser;
	m_pStateLevel = levelParser.parseLevel(level.c_str());
}
