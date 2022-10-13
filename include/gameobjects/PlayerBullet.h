#pragma once
#include "gameobjects/BaseBullet.h"

class Alien;
class AlienBoss;
class Block;

/// <summary>
/// 
/// </summary>
class PlayerBullet :
	public BaseBullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, std::vector<Alien*>* levelAliensPtr, AlienBoss* alienBossPtr, std::vector<Block*>* levelBlocksPtr) ;

	virtual void drawObject() override;
	virtual void updateObject() override;

private:

	// Pointers to other level objects to perform collision checks against
	std::vector<Alien*>* m_pAllAliens;
	std::vector<Block*>* m_pAllBlocks;
	AlienBoss* m_pAlienBoss;
};

class PlayerBulletCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new PlayerBullet();
	}
};
