#include "pch.h"
#include "gameobjects/utility/GameObjectFactory.h"

#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/Block.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/ClickButton.h"
#include "gameobjects/Player.h"
#include "gameobjects/PlayerLives.h"
#include "gameobjects/TextObject.h"

GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;

// 

/// <summary>
///	Initialize the GameObjectFactory, registering the types for the LevelParser
/// Note only the ones that appear in .tmx files need to be registered
/// </summary>
bool GameObjectFactory::init()
{
	registerType("ClickButton", new ClickButtonCreator());
	registerType("Player", new PlayerCreator());
	registerType("Alien", new AlienCreator());
	registerType("SDLGameObject", new SDLGameObjectCreator());
	registerType("PlayerLives", new PlayerLivesCreator());
	registerType("TextObject", new TextObjectCreator());
	registerType("CheckboxButton", new CheckboxButtonCreator());
	registerType("AlienBoss", new AlienBossCreator());
	registerType("Block", new BlockCreator());

	return true;
}

/// <summary>
/// Clean up the GameObjectFactory
/// </summary>
void GameObjectFactory::clean()
{
	// loop through m_creators to destroy all creator classes
}

/// <summary>
/// Register a new type with the factory and add it to the map
/// </summary>
bool GameObjectFactory::registerType(const std::string& typeID, BaseCreator* pCreator)
{
	assert(pCreator);

	// Ensure type doesn't already exist
	if (m_creators.count(typeID))
	{
		delete pCreator;
		return false;
	}

	// Assign to map
	m_creators.insert({ typeID, pCreator });

	return true;
}

/// <summary>
/// If typeID exists, use the creator object for that type to create
/// and return a new instance of it as a pointer to BaseGameObject
/// </summary>
BaseGameObject* GameObjectFactory::createGameObject(const std::string& typeID)
{
	// Verify that type exists
	if (!m_creators.count(typeID))
	{
		std::cout << "Could not find type: " << typeID << std::endl;
		return nullptr;
	}

	// Return created BaseGameObject
	BaseCreator* pCreator = m_creators.at(typeID);
	return pCreator->createGameObject();
}
