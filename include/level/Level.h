#pragma once

class LevelParser;
class TileLayer;

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

