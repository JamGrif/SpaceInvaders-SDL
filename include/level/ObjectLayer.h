#pragma once
#include "BaseLayer.h"

class BaseGameObject;
class Alien;
class Player;
class AlienBoss;

#include "level/LevelParser.h"

// The ObjectLayer draws and updates the objects for this layer
class ObjectLayer :
    public BaseLayer
{
public:
	ObjectLayer();
	~ObjectLayer();

	virtual void updateLayer();
	virtual void renderLayer();

	std::vector<BaseGameObject*>& getGameObjects() { return m_layerGameObjects; }

	std::vector<Alien*>& getAlienObjects() { return m_layerAlienObjects; }

	Player* getPlayerObject() const { return m_layerPlayer; }

	AlienBoss* getAlienBossObject() const { return m_layerAlienBoss; }

private:
	std::vector<BaseGameObject*> m_layerGameObjects;
	std::vector<Alien*> m_layerAlienObjects;
	Player* m_layerPlayer;
	AlienBoss* m_layerAlienBoss;

	void setPlayer(Player* p) { m_layerPlayer = p; }
	void setAlienBoss(AlienBoss* a) { m_layerAlienBoss = a; }

	friend LevelParser;
};

