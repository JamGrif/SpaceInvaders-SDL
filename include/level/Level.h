#pragma once

class BaseLayer;
class LevelParser;

// Holds any information needed to know about the tileset
// Passed into the parser when its time to load the map
struct Tileset
{
	std::string name;		// Name of tileset in editor
	int firstGidID = 0;		// First global tile ID of this tileset (This ID maps to the first tile in this tileset)
	int tileWidth	= 0;	// Pixel size of an individual tile width
	int tileHeight	= 0;	// Pixel size of an individual tile height
	int numColumns	= 0;	// Number of tile frames in a row
	int spacing		= 0;	// Pixel space between each sprite frame
	int margin		= 0;	// Pixel space from the edge to first sprite frame
	int width		= 0;	// Total pixel width of complete sprite
	int height		= 0;	// Total pixel height of complete sprite
};

enum class LayerIndex
{
	tilesetLayer	= 0,
	//objectLayer		= 1
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

	void addTileLayer(std::unique_ptr<BaseLayer> layer);

private:
	// All tilesets used in this level
	std::vector<Tileset> m_tilesets;

	// All layers used in this level
	std::vector<std::unique_ptr<BaseLayer>> m_layers;

	// Ensures that a level can only be created from the LevelParser class
	Level();

	// LevelParser class now has access to the private constructor of Level and can return new instances
	friend class LevelParser; 
};

