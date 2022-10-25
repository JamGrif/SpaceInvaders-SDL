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

	virtual void				loadObject(std::unique_ptr<LoaderParams> pParams, std::vector<std::shared_ptr<Alien>>* pLevelAliens, std::weak_ptr<AlienBoss> pAlienBoss, std::vector<std::shared_ptr<Block>>* pLevelBlocks);

	virtual void				drawObject() override;
	virtual void				updateObject() override;

private:

	// Pointers to other level objects to perform collision checks against
	std::vector<std::shared_ptr<Alien>>* m_pAllAliens;
	std::vector<std::shared_ptr<Block>>* m_pAllBlocks;
	std::weak_ptr<AlienBoss>	m_pAlienBoss;
};

class PlayerBulletCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<PlayerBullet>();
	}
};
