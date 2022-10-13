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

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, Player* levelPlayer, std::vector<Block*>* levelBlocksPtr);

	virtual void drawObject() override;
	virtual void updateObject() override;

private:

	// Pointers to other level objects to perform collision checks against
	std::vector<Block*>* m_pAllBlocks;
	Player* m_pLevelPlayer;

	// Used to find if alien has left screen
	int m_screenHeight;
};


class AlienBulletCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new AlienBullet();
	}
};
