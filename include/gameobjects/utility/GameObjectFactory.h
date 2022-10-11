#pragma once

class BaseGameObject;

/// <summary>
/// Only purpose is the creation of a specific object
/// </summary>
class BaseCreator
{
public:
	virtual BaseGameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

/// <summary>
/// Use in the LevelParser to create objects of specific types.
/// Can only create objects of types that have been registered in the registerType function
/// </summary>
class GameObjectFactory
{
public:

	bool init();
	void clean();

	bool registerType(std::string typeID, BaseCreator* pCreator);

	BaseGameObject* create(std::string typeID);

	static GameObjectFactory* Instance() // Instance get
	{
		if (!s_pInstance)
			s_pInstance = new GameObjectFactory();
		return s_pInstance;
	}

private:
	static GameObjectFactory* s_pInstance;

	// Maps a string (the typeID of the object) to its class creator
	std::unordered_map<std::string, BaseCreator*> m_creators;
};
typedef GameObjectFactory TheGameObjectFactory;
