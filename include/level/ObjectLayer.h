#pragma once
#include "Layer.h"

class GameObject;

// The ObjectLayer draws and updates the objects for this layer
class ObjectLayer :
    public Layer
{
public:
	virtual void update();
	virtual void render();

	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}

private:
	std::vector<GameObject*> m_gameObjects;

};

