#pragma once
#include "BaseLayer.h"

class BaseGameObject;
class Alien;

// The ObjectLayer draws and updates the objects for this layer
class ObjectLayer :
    public BaseLayer
{
public:
	ObjectLayer();
	~ObjectLayer();

	virtual void updateLayer();
	virtual void renderLayer();

	std::vector<BaseGameObject*>& getGameObjects()
	{
		return m_layerGameObjects;
	}

	std::vector<Alien*>& getAlienObjects()
	{
		return m_layerAlienObjects;
	}
	

private:
	std::vector<BaseGameObject*> m_layerGameObjects;
	std::vector<Alien*> m_layerAlienObjects;

};

