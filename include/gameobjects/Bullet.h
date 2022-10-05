#pragma once
#include "SDLGameObject.h"


class PlayerBullet :
    public SDLGameObject
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();


};

class PlayerBulletCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new PlayerBullet();
	}
};

