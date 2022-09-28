#pragma once
#include "SDLGameObject.h"

#include "GameObjectFactory.h"


class Player :
    public SDLGameObject
{
public:
    Player();
    ~Player();

    virtual void draw();
    virtual void update();
    virtual void clean();
	virtual void load(const LoaderParams* pParams);

private:
    void handleInput();

};

class PlayerCreator :
	public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};

