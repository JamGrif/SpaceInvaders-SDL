#pragma once
#include "BaseBullet.h"

class Alien;
class AlienBoss;
class Block;

class PlayerBullet :
	public BaseBullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, std::vector<Alien*>* levelAliensPtr, AlienBoss* alienBossPtr, std::vector<Block*>* levelBlocksPtr) ;

	virtual void drawObject() override;
	virtual void updateObject() override;


	//bool getDestroy() const { return m_bDestroy; }

private:

	//bool m_bDestroy;

	// All alive aliens + boss + blocks to perform collision checks with
	std::vector<Alien*>* m_pAllAliens;
	AlienBoss* m_pAlienBoss;
	std::vector<Block*>* m_pAllBlocks;
};

class PlayerBulletCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new PlayerBullet();
	}
};
