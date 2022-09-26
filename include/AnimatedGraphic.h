#pragma once
#include "SDLGameObject.h"
class AnimatedGraphic :
    public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;

};

