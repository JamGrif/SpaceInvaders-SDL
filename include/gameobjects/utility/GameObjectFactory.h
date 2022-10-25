#pragma once

class BaseGameObject;

/// <summary>
/// Registers an object with the GameObjectFactory which is used to create objects from the level editor files (.tmx)
/// Only required for objects that are spawned from the level editor
/// Any new inherited game objects must also inherit and implement this class 
/// </summary>
class BaseCreator
{
public:
	virtual std::shared_ptr<BaseGameObject> createGameObject() const = 0;
	BaseCreator() {}
	virtual ~BaseCreator() {}
};

/// <summary>
/// Use in the LevelParser to create objects of specific types.
/// Can only create objects of types that have been registered in the registerType function
/// </summary>
class GameObjectFactory
{
public:
	bool							init();
	void							clean();

	bool							registerType(const std::string& typeID, std::unique_ptr<BaseCreator> pCreator);

	std::shared_ptr<BaseGameObject> createGameObject(const std::string& typeID);

	static GameObjectFactory*		Instance() // Get instance
	{
		static GameObjectFactory* s_pInstance = new GameObjectFactory;
		return s_pInstance;
	}

private:

	// Maps a string (the typeID of the object) to its class creator
	std::unordered_map<std::string, std::unique_ptr<BaseCreator>> m_creators;

	GameObjectFactory() {}										// Prevent outside unwanted construction
	GameObjectFactory(const GameObjectFactory&) {}				// Prevent construction by copying
	GameObjectFactory& operator=(const GameObjectFactory&) {}	// Prevent assignment
	~GameObjectFactory() {}										// Prevent outside unwanted destruction
};
typedef GameObjectFactory TheGameObjectFactory;
