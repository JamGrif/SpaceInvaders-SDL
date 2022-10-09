#pragma once


class Level;
class BaseLayer;
class TiXmlElement;
struct Tileset;

// Parser for the .tmx files (.xml) and creates levels from them
class LevelParser
{
public:

	// Called whenever we want to create a level
	Level* parseLevel(const char* levelFile);

private:

	// Layers
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<BaseLayer*>* pLayers, const std::vector<Tileset>* pTilesets);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<BaseLayer*>* pLayers);

	// Textures
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

	int m_tileSize;
	int m_width;
	int m_height;

};

