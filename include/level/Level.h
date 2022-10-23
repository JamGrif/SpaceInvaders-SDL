#pragma once

class LevelParser;
class TileLayer;

// Holds any information needed to know about the tileset
// Passed into the parser when its time to load the map
struct Tileset
{
	std::string name;			// Name of tileset in editor
	int32_t firstGidID	= 0;	// First global tile ID of this tileset (This ID maps to the first tile in this tileset)
	int32_t tileWidth	= 0;	// Pixel size of an individual tile width
	int32_t tileHeight	= 0;	// Pixel size of an individual tile height
	int32_t numColumns	= 0;	// Number of tile frames in a row
	int32_t spacing		= 0;	// Pixel space between each sprite frame
	int32_t margin		= 0;	// Pixel space from the edge to first sprite frame
	int32_t width		= 0;	// Total pixel width of complete sprite
	int32_t height		= 0;	// Total pixel height of complete sprite
};

/// <summary>
/// Contains the layers, allowing storage and usage of them
/// The level is created from a .tmx file created in the level editor
/// </summary>
class Level
{
public:
	~Level();

	void					updateLevel();
	void					renderLevel();

	void					addTileLayer(std::unique_ptr<TileLayer> layer);

private:

	// All layers used in this level
	std::unique_ptr<TileLayer> m_pTileLayer;

	// Ensures that a level can only be created from the LevelParser class
	Level();

	// LevelParser class now has access to the private constructor of Level and can return new instances
	friend class LevelParser; 
};

