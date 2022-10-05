#include "pch.h"
#include "level/Level.h"

#include "level/BaseLayer.h"

Level::~Level()
{
	for (auto layer : m_layers)
	{
		delete layer;
	}
}

void Level::updateLevel()
{
	for (auto layer : m_layers)
	{
		layer->updateLayer();
	}
}

void Level::renderLevel()
{
	for (auto layer : m_layers)
	{
		layer->renderLayer();
	}
}

std::vector<Tileset>* Level::getLevelTilesets()
{
	return &m_tilesets;
}

std::vector<BaseLayer*>* Level::getLevelLayers()
{
	return &m_layers;
}

BaseLayer* Level::getLayer(LayerIndex layerIndex)
{
	return m_layers.at(static_cast<size_t>(layerIndex));
}

Level::Level()
{
}
