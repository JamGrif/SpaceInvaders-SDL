#pragma once

class BaseLayer;
class LevelParser;

// Holds any information needed to know about the tileset
// Passed into the parser when its time to load the map
struct Tileset
{
	int firstGridID = 0;
	int tileWidth	= 0;
	int tileHeight	= 0;
	int spacing		= 0;
	int margin		= 0;
	int width		= 0;
	int height		= 0;
	int numColumns	= 0;
	std::string name;
};

enum class LayerIndex
{
	tilesetLayer = 0,
	objectLayer = 1
};

// Holds the tileset and main purpose is to store, draw and update the layers
class Level
{
public:
	~Level();

	void updateLevel();
	void renderLevel();

	std::vector<Tileset>* getLevelTilesets();
	std::vector<BaseLayer*>* getLevelLayers();

	BaseLayer* getLayer(LayerIndex layerIndex);

private:
	std::vector<Tileset> m_tilesets;
	std::vector<BaseLayer*> m_layers;

	// Ensures that a level can only be created from the LevelParser class
	Level();
	friend class LevelParser; // LevelParser class now has access to the private constructor of Level and can return new instances
};

