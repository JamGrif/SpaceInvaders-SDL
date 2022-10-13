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
	int spacing		= 0;	// Pixel space between each sprite frame
	int margin		= 0;	// Pixel space from the edge to first sprite frame
	int width		= 0;
	int height		= 0;
	int numColumns	= 0;
	std::string name;
};

enum class LayerIndex
{
	tilesetLayer	= 0,
	objectLayer		= 1
};

/// <summary>
/// Contains the layers, allowing storage and usage of them
/// The level is created from a .tmx file created in the level editor
/// </summary>
class Level
{
public:
	~Level();

	void						updateLevel();
	void						renderLevel();

	std::vector<Tileset>*		getLevelTilesets() { return &m_tilesets; }

	std::vector<BaseLayer*>*	getLevelLayers() { return &m_layers;}

	BaseLayer*					getLayer(LayerIndex layerIndex) { return m_layers.at(static_cast<size_t>(layerIndex)); }

private:
	// All tilesets used in this level
	std::vector<Tileset> m_tilesets;

	// All layers used in this level
	std::vector<BaseLayer*> m_layers;

	// Ensures that a level can only be created from the LevelParser class
	Level();

	// LevelParser class now has access to the private constructor of Level and can return new instances
	friend class LevelParser; 
};

