#include "pch.h"
#include "level/Level.h"

#include "level/TileLayer.h"

Level::~Level()
{
	//for (auto layer : m_layers)
	//{
	//	delete layer;
	//}
	//std::cout << "destroyed level" << std::endl;
	//for (auto& t : m_tilesets)
	//{
	//	delete t;
	//}
	//std::cout << "level tileset size " << m_tilesets.size() << std::endl;
}

/// <summary>
/// Update all layers used in this level
/// </summary>
void Level::updateLevel()
{
	//for (const auto& layer : m_layers)
	//{
	//	layer->updateLayer();
	//}
	m_pTileLayer->updateLayer();
}

/// <summary>
/// Draw all layers used in this level
/// </summary>
void Level::renderLevel()
{
	//for (const auto& layer : m_layers)
	//{
	//	layer->renderLayer();
	//}
	m_pTileLayer->renderLayer();
}

void Level::addTileLayer(std::unique_ptr<TileLayer> layer)
{
	//m_layers.push_back(std::move(layer));
	m_pTileLayer = std::move(layer);
}

Level::Level()
{
}
