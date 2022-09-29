#pragma once



class Layer;
class LevelParser;

// Holds any information needed to know about the tileset
// Passed into the parser when its time to load the map
struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};


// Holds the tileset and main purpose is to store, draw and update the layers
class Level
{
public:
	~Level();

	void update();
	void render();

	std::vector<Tileset>* getTilesets();
	std::vector<Layer*>* getLayers();

private:
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;

	// Ensures that a level can only be created from the LevelParser class
	Level();
	friend class LevelParser; // LevelParser class now has access to the private constructor of Level and can return new instances
};

