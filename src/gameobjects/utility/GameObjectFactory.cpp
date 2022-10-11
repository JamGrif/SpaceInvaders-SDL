#include "pch.h"
#include "gameobjects/utility/GameObjectFactory.h"

#include "gameobjects/MenuButton.h"
#include "gameobjects/Alien.h"
#include "gameobjects/Player.h"
#include "gameobjects/TextObject.h"
#include "gameobjects/PlayerLives.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/Block.h"

GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;

// Register types for the LevelParser (only ones that appear in .tmx files)
bool GameObjectFactory::init()
{
	registerType("MenuButton", new MenuButtonCreator());
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


void GameObjectFactory::clean()
{
	// loop through m_creators to destroy all creator classes
}

/// <summary>
/// Register a new type with the factory and add it to the map
/// </summary>
bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
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
/// If typeID exists, use the creator object for that type to create and return a new instance of it as a pointer to BaseGameObject
/// </summary>
BaseGameObject* GameObjectFactory::create(std::string typeID)
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
