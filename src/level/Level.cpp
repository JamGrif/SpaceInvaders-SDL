#include "pch.h"
#include "level/Level.h"

#include "level/BaseLayer.h"

Level::~Level()
{
	//for (auto layer : m_layers)
	//{
	//	delete layer;
	//}
	//std::cout << "destroyed level" << std::endl;
}

/// <summary>
/// Update all layers used in this level
/// </summary>
void Level::updateLevel()
{
	for (const auto& layer : m_layers)
	{
		layer->updateLayer();
	}
}

/// <summary>
/// Draw all layers used in this level
/// </summary>
void Level::renderLevel()
{
	for (const auto& layer : m_layers)
	{
		layer->renderLayer();
	}
}

void Level::addTileLayer(std::unique_ptr<BaseLayer> layer)
{
	m_layers.push_back(std::move(layer));
}

Level::Level()
{
}
