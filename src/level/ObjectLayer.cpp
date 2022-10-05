#include "pch.h"
#include "level/ObjectLayer.h"

#include "gameobjects/BaseGameObject.h"
#include "gameobjects/Alien.h"

ObjectLayer::ObjectLayer()
{

}

ObjectLayer::~ObjectLayer()
{
	for (auto object : m_layerGameObjects)
	{
		delete object;
	}
	m_layerGameObjects.clear();

	for (auto alien : m_layerAlienObjects)
	{
		delete alien;
	}
	m_layerAlienObjects.clear();
}

void ObjectLayer::updateLayer()
{
	for (auto object : m_layerGameObjects)
	{
		object->updateObject();
	}

	for (auto alien : m_layerAlienObjects)
	{
		alien->updateObject();
	}
}

void ObjectLayer::renderLayer()
{
	for (auto object : m_layerGameObjects)
	{
		object->drawObject();
	}

	for (auto alien : m_layerAlienObjects)
	{
		alien->drawObject();
	}
}

