#pragma once
#include "SDLGameObject.h"


class AnimatedGraphic :
    public SDLGameObject
{
public:
	AnimatedGraphic(int animSpeed = 2);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

private:
	int m_animSpeed;

};

class AnimatedGraphicCreator :
	public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};
