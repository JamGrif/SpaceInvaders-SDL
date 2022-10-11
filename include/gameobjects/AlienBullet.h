#pragma once
#include "BaseBullet.h"

class Player;
class Block;

class AlienBullet
	: public BaseBullet
{
public:
	AlienBullet();
	~AlienBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, Player* levelPlayer, std::vector<Block*>* levelBlocksPtr);

	virtual void drawObject() override;
	virtual void updateObject() override;


	//bool getDestroy() const { return m_bDestroy; }

private:

	//bool m_bDestroy;

	Player* m_pLevelPlayer;
	std::vector<Block*>* m_pAllBlocks;

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
