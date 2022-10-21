#include "pch.h"
#include "level/ObjectLayer.h"

//#include "gameobjects/Alien.h"
//#include "gameobjects/BaseGameObject.h"
//#include "gameobjects/Block.h"
//
//ObjectLayer::ObjectLayer()
//	:m_layerPlayer(nullptr), m_layerAlienBoss(nullptr)
//{
//}
//
//ObjectLayer::~ObjectLayer()
//{
//	for (auto object : m_layerGameObjects)
//	{
//		delete object;
//	}
//	m_layerGameObjects.clear();
//
//	for (auto alien : m_layerAlienObjects)
//	{
//		delete alien;
//	}
//	m_layerAlienObjects.clear();
//
//	m_layerPlayer = nullptr;
//}
//
///// <summary>
///// Updates all objects created in the level parser
///// </summary>
//void ObjectLayer::updateLayer()
//{
//	for (auto object : m_layerGameObjects)
//	{
//		object->updateObject();
//	}
//
//	for (auto alien : m_layerAlienObjects)
//	{
//		alien->updateObject();
//	}
//
//	for (auto block : m_layerBlocks)
//	{
//		block->updateObject();
//	}
//}
//
///// <summary>
///// Draws all objects created in the level parser
///// </summary>
//void ObjectLayer::renderLayer()
//{
//	for (auto object : m_layerGameObjects)
//	{
//		object->drawObject();
//	}
//
//	for (auto alien : m_layerAlienObjects)
//	{
//		alien->drawObject();
//	}
//
//	for (auto block : m_layerBlocks)
//	{
//		block->drawObject();
//	}
//}
//
