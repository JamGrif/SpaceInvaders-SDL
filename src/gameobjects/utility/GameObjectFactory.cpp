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

/// <summary>
///	Initialize the GameObjectFactory, registering the types for the LevelParser
/// Note only the ones that appear in .tmx files need to be registered
/// </summary>
bool GameObjectFactory::init()
{
	registerType("ClickButton",		std::move(std::make_unique<ClickButtonCreator>()));
	registerType("Player",			std::move(std::make_unique<PlayerCreator>()));
	registerType("Alien",			std::move(std::make_unique<AlienCreator>()));
	registerType("SDLGameObject",	std::move(std::make_unique<SDLGameObjectCreator>()));
	registerType("PlayerLives",		std::move(std::make_unique<PlayerLivesCreator>()));
	registerType("TextObject",		std::move(std::make_unique<TextObjectCreator>()));
	registerType("CheckboxButton",	std::move(std::make_unique<CheckboxButtonCreator>()));
	registerType("AlienBoss",		std::move(std::make_unique<AlienBossCreator>()));
	registerType("Block",			std::move(std::make_unique<BlockCreator>()));

	return true;
}

/// <summary>
/// Clean up the GameObjectFactory
/// </summary>
void GameObjectFactory::clean()
{
	// Wipe all created creator classes
	m_creators.clear();
}

/// <summary>
/// Register a new type with the factory and add it to the map
/// </summary>
bool GameObjectFactory::registerType(const std::string& typeID, std::unique_ptr<BaseCreator> pCreator)
{
	assert(pCreator);

	// Ensure type doesn't already exist
	if (m_creators.count(typeID))
	{
		std::cout << typeID << " type already exists" << std::endl;
		return false;
	}

	// Assign to map
	m_creators.insert({ typeID, std::move(pCreator) });

	return true;
}

/// <summary>
/// If typeID exists, use the creator object for that type to create
/// and return a new instance of it as a pointer to BaseGameObject
/// </summary>
std::shared_ptr<BaseGameObject> GameObjectFactory::createGameObject(const std::string& typeID)
{
	// Verify that type exists
	if (!m_creators.count(typeID))
	{
		std::cout << "Could not find type: " << typeID << std::endl;
		return nullptr;
	}

	// Return created BaseGameObject
	//std::unique_ptr<BaseCreator> pCreator = m_creators.at(typeID);
	return m_creators.at(typeID)->createGameObject();
}
