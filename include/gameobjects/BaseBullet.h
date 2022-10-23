#pragma once
#include "gameobjects/SDLGameObject.h"

// Y value of the space invaders finish line (darkened line in level)
#define LEVEL_FINISH_LINE_Y 520

/// <summary>
/// Base class for a Bullet object
/// </summary>
class BaseBullet :
	public SDLGameObject
{
public:
	BaseBullet();
	~BaseBullet();

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams) override;

	virtual void	drawObject() override;
	virtual void	updateObject() = 0;

protected:
};







