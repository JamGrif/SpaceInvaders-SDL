#include "pch.h"
#include "gameobjects/utility/GameObjectFactory.h"


GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
	std::unordered_map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	// if the type is already registered, do nothing
	if (it != m_creators.end())
	{
		delete pCreator;
		return false;
	}

	// Assign to map
	m_creators[typeID] = pCreator;
	return true;
}

BaseGameObject* GameObjectFactory::create(std::string typeID)
{
	std::unordered_map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	if (it == m_creators.end())
	{
		std::cout << "Could not find type: " << typeID << std::endl;
		return nullptr;
	}

	BaseCreator* pCreator = (*it).second;
	return pCreator->createGameObject();
}

/// <summary>
/// Checks if a type exists and returns true or false on result
/// </summary>
bool GameObjectFactory::checkIfExist(std::string typeID)
{
	std::unordered_map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	return it == m_creators.end() ? false : true;

}
