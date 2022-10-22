#pragma once

class Level;
class BaseLayer;
class TiXmlElement;
struct Tileset;

class BaseGameObject;

/// <summary>
/// Parser for a .tmx file, creating and filling out a level object from it with its associative layers
/// </summary>
class LevelParser
{
public:

	Level* parseLevel(const std::string& filepath, std::vector<std::shared_ptr<BaseGameObject>>& allGameObjects);

private:

	// Level to be created and returned
	Level* createdLevel = nullptr;

	// Tileset created during level parsing
	std::unique_ptr<Tileset> pTileset;

	// Layers
	void parseTileLayer(const TiXmlElement& pLayerRoot);
	void parseObjectLayer(const TiXmlElement& pObjectGroupRoot, std::vector<std::shared_ptr<BaseGameObject>>& allGameObjects); //

	// Sprites
	void parseSprites(const std::vector<std::pair<std::string, std::string>>& spritesToLoad); //
	void parseTilesets(const TiXmlElement& pTilesetRoot); //

	// Dimensions, in pixels, of an individual tile
	int m_tilePixelSize;

	// Dimensions, in tiles, of the entire .tmx file
	int m_levelTileWidth;
	int m_levelTileHeight;
};

