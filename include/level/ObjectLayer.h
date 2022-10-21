#pragma once
#include "level/BaseLayer.h"
//
//#include "level/LevelParser.h"
//
//class BaseGameObject;
//class Alien;
//class Player;
//class AlienBoss;
//class Block;
//
///// <summary>
///// ObjectLayer draws and updates any objects created from the level parser in the level editor
///// Only objects that are created in the object layer in the level editor are here
///// </summary>
//class ObjectLayer :
//    public BaseLayer
//{
//public:
//	ObjectLayer();
//	~ObjectLayer();
//
//	virtual void updateLayer() override;
//	virtual void renderLayer() override;
//
//	// Get specific objects in current level
//	std::vector<BaseGameObject*>& getGameObjects() { return m_layerGameObjects; }
//
//	std::vector<Alien*>& getAlienObjects() { return m_layerAlienObjects; }
//
//	Player* getPlayerObject() const { return m_layerPlayer; }
//
//	AlienBoss* getAlienBossObject() const { return m_layerAlienBoss; }
//
//	std::vector<Block*>& getBlockObjects() { return m_layerBlocks; }
//
//private:
//	std::vector<BaseGameObject*> m_layerGameObjects;
//
//	std::vector<Alien*> m_layerAlienObjects;
//	std::vector<Block*> m_layerBlocks;
//	Player* m_layerPlayer;
//	AlienBoss* m_layerAlienBoss;
//
//	void setPlayer(Player* p) { m_layerPlayer = p; }
//	void setAlienBoss(AlienBoss* a) { m_layerAlienBoss = a; }
//
//	friend LevelParser;
//};

