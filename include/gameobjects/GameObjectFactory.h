#pragma once

// Have a factory that contains an std::map that maps a string (the type of the object) to a small class called Creator
// The Creator classes only purpose is the creation of a specific object
// Will register a new type with the factory using a function that takes a string (the ID) and a Creator class and adds them to the factory's map

#include <map>
#include "gameobjects/GameObject.h"

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

// Could change implementation to make GameObjectFactory a singleton
class GameObjectFactory
{
public:

	// Takes the ID we want to associate the object type with (as a string) and the creator object for that class
	// It then attempts to find the type using the std::map.find function
	// If the type is found, then it is already registered, so it deletes the passed in pointer and returns false
	// If the type is not already registered, then it can be assigned to the map and then true is returned
	// Basically, just a way to add types to the map
	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

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

	// The function looks for the type in the map, but if the type is not found it returns 0
	// If the type is found then we use the creator object for that type to return a new instance of it as a pointer to GameObject
	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "Could not find type: " << typeID << std::endl;
			return NULL;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

	static GameObjectFactory* Instance(); // Singleton
private:
	//GameObjectFactory();
	static GameObjectFactory* s_pInstance;

	// Map holds the important elements of the factory, the functions of the class either add or remove from this map.
	std::map<std::string, BaseCreator*> m_creators;
};
typedef GameObjectFactory TheGameObjectFactory;
