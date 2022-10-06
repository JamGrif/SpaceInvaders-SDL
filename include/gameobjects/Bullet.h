#pragma once
#include "SDLGameObject.h"

class Alien;
class Player;


class PlayerBullet :
    public SDLGameObject
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams, std::vector<Alien*>* levelAliensPtr);

	virtual void drawObject();
	virtual void updateObject();

	bool getDestroy();

private:

	bool m_bDestroy;

	// All alive aliens to perform collision checks with
	std::vector<Alien*>* m_pAllAliens;
};

class AlienBullet
	: public SDLGameObject
{
public:
	AlienBullet();
	~AlienBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

	bool getDestroy();

private:

	bool m_bDestroy;

	Player* m_pPlayer;

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

