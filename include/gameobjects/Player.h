#pragma once
#include "SDLGameObject.h"

class Player :
    public SDLGameObject
{
public:
    Player();
    ~Player();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

    virtual void drawObject();
    virtual void updateObject();

private:

};

class PlayerCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new Player();
	}
};

