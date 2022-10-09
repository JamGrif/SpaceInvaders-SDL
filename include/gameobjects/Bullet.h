#pragma once
#include "SDLGameObject.h"

class Alien;
class AlienBoss;
class Player;


class PlayerBullet :
    public SDLGameObject
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, std::vector<Alien*>* levelAliensPtr, AlienBoss* alienBossPtr);

	virtual void drawObject();
	virtual void updateObject();


	bool getDestroy() const { return m_bDestroy; }

private:

	bool m_bDestroy;

	// All alive aliens + boss to perform collision checks with
	std::vector<Alien*>* m_pAllAliens;
	AlienBoss* m_pAlienBoss;
};

class AlienBullet
	: public SDLGameObject
{
public:
	AlienBullet();
	~AlienBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, Player* levelPlayer);

	virtual void drawObject();
	virtual void updateObject();


	bool getDestroy() const { return m_bDestroy; }

private:

	bool m_bDestroy;

	Player* m_pLevelPlayer;

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

class PlayerBulletCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new PlayerBullet();
	}
};

