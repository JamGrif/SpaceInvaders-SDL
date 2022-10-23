#pragma once
#include "gameobjects/BaseBullet.h"

class Player;
class Block;

/// <summary>
/// Alien bullet object that appear during gameplay
/// </summary>
class AlienBullet :
	public BaseBullet
{
public:
	AlienBullet();
	~AlienBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> pParams, std::weak_ptr<Player> pLevelPlayer, std::vector<std::shared_ptr<Block>>* pLevelBlocks);

	virtual void drawObject() override;
	virtual void updateObject() override;

private:

	// Other level objects to perform collision checks against
	std::vector<std::shared_ptr<Block>>* m_pAllBlocks;
	std::weak_ptr<Player> m_pLevelPlayer;
};


class AlienBulletCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<AlienBullet>();
	}
};
