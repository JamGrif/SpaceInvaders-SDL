#include "pch.h"
#include "level/LevelParser.h"

#include "core/SpriteManager.h"
#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/BaseGameObject.h"
#include "gameobjects/Block.h"
#include "gameobjects/Player.h"
#include "gameobjects/PlayerLives.h"
#include "level/Level.h"
#include "level/TileLayer.h"
#include "level/ObjectLayer.h"

#include "Base64/base64.h"		// Decode the level data
#include "zlib/zlib.h"			// Decompress the level data
#include "tinyXML/tinyxml.h"	// Read the level data

#define LEVEL_PATH_PREFIX "res/levels/"
#define TILESET_PATH_PREFIX "res/levels/"
#define SPRITE_PATH_PREFIX "res/sprites/"

/// <summary>
/// Called whenever a .tmx file needs to be parsed at filepath
/// </summary>
Level* LevelParser::parseLevel(const std::string& filepath)
{
	// Create the TinyXML document and load the map XML
	TiXmlDocument levelDocument;

	if (!levelDocument.LoadFile(LEVEL_PATH_PREFIX + filepath))
	{
		std::cout << levelDocument.ErrorDesc() << std::endl;
		return nullptr;
	}

	// Create the level object
	Level* pLevel = new Level();

	// Get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	// Know that properties is the first child of the root
	TiXmlElement* pProperties = pRoot->FirstChildElement();

	// Parse the textures needed for this level, which has been added to properties
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures(e);
		}
	}

	// Parse the tileset
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getLevelTilesets());
		}
	}

	// Parse any layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLevelLayers());
			}
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				parseTileLayer(e, pLevel->getLevelLayers(), pLevel->getLevelTilesets());
			}
		}
	}

	// .tmx file has been fully parsed, so return newly created level
	return pLevel;
}

/// <summary>
/// The TileLayer is the layer the tileset is drawn too in the level editor
/// Uses the Base64 and zlib libraries to decode and decompress the data
/// </summary>
void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<BaseLayer*>* pLayers, const std::vector<Tileset>* pTilesets)
{
	// Create new TileLayer instance
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	// Tile data
	std::vector<std::vector<int>> data; // Holds the decoded and uncompressed tiledata

	std::string decodedIDs; // base64 decoded information
	TiXmlElement* pDataNode = nullptr;

	// Search for the node that is needed (data node)
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	// Once correct node is found, can get the text from within it (the encoded/compressed data)
	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		// Use the Base64 decoder to decode it
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// The decodedIDs variable is now a base64 decoded string
	// Now to use the zlib library to decompress the data

	// Uncompress zlib compression
	uLongf numGids = m_width * m_height * sizeof(int);

	std::vector<unsigned int> gids(numGids);

	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), static_cast<uLong>(decodedIDs.size()));

	// The ids vector now contains all of the tile IDs
	// Now to set the size of the data vector so it can be filled with the tile IDs
	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	// Now to fill our data array with the correct values
	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}

	// Finally, set this layers tile data and then push the layer into the layers array of the Level
	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);
}

/// <summary>
/// The object layer is all the objects added in the level editor
/// The object layer handles all the updating and drawing of only the objects created from this layer
/// </summary>
void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<BaseLayer*>* pLayers)
{
	// Create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() != std::string("object"))
			continue;

		// Create object of type and check it was made
		BaseGameObject* pGameObject = TheGameObjectFactory::Instance()->createGameObject(e->Attribute("class"));
		if (!pGameObject)
			continue;

		std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();

		// Get the initial node values type, x and y
		e->Attribute("x", &tempLoaderParams->xPos);
		e->Attribute("y", &tempLoaderParams->yPos);

		// Get the property values
		for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
		{
			if (properties->Value() == std::string("properties"))
			{
				for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
				{
					// Only read the property element of properties
					if (property->Value() != std::string("property"))
						continue;

					if (property->Attribute("name") == std::string("numFrames")) // Check for the name of the property rather than grabbing the attribute directly
					{
						property->Attribute("value", &tempLoaderParams->numFrames);
					}
					else if (property->Attribute("name") == std::string("textureID"))
					{
						tempLoaderParams->textureID = property->Attribute("value");
					}
					else if (property->Attribute("name") == std::string("selectCallbackID"))
					{
						property->Attribute("value", &tempLoaderParams->selectCallbackID);
					}
					else if (strcmp(property->Attribute("name"), "animationSpeed") == 0)
					{
						property->Attribute("value", &tempLoaderParams->animationSpeed);
					}
					else if (property->Attribute("name") == std::string("livesRequired"))
					{
						property->Attribute("value", &tempLoaderParams->livesRequired);
					}
					else if (property->Attribute("name") == std::string("movementSpeed"))
					{
						double x;
						property->Attribute("value", &x);
						tempLoaderParams->movementSpeed = static_cast<float>(x);
					}
					else if (property->Attribute("name") == std::string("text"))
					{
						tempLoaderParams->text = property->Attribute("value");
					}
					else if (property->Attribute("name") == std::string("checkboxStateCallbackID"))
					{
						property->Attribute("value", &tempLoaderParams->checkboxStateCallbackID);
					}
					else if (property->Attribute("name") == std::string("scoreWorth"))
					{
						property->Attribute("value", &tempLoaderParams->scoreWorth);
					}
					else if (property->Attribute("name") == std::string("textCallbackID"))
					{
						property->Attribute("value", &tempLoaderParams->textCallbackID);
					}
					else if (property->Attribute("name") == std::string("textSize"))
					{
						property->Attribute("value", &tempLoaderParams->textSize);
					}

				}
			}
		}

		// Create the object just like the state parser
		pGameObject->loadObject(tempLoaderParams);

		// If the object is an Alien then put it in a separate vector, otherwise put it in the normal vector
		if (dynamic_cast<AlienBoss*>(pGameObject))
		{
			pObjectLayer->setAlienBoss(dynamic_cast<AlienBoss*>(pGameObject));
			pObjectLayer->getGameObjects().push_back(pGameObject);
			continue;
		}

		if (dynamic_cast<Block*>(pGameObject))
		{
			Block* temp = dynamic_cast<Block*>(pGameObject);
			pObjectLayer->getBlockObjects().push_back(temp);
			continue;
		}

		if (dynamic_cast<Alien*>(pGameObject))
		{
			Alien* temp = dynamic_cast<Alien*>(pGameObject);
			pObjectLayer->getAlienObjects().push_back(temp);
		}
		else
		{
			pObjectLayer->getGameObjects().push_back(pGameObject);

			if (dynamic_cast<Player*>(pGameObject))
				pObjectLayer->setPlayer(dynamic_cast<Player*>(pGameObject));
		}

	}


	// Once loaded all the objects for this layer, we can push it into our level layer array
	pLayers->push_back(pObjectLayer);
}

/// <summary>
/// Creates all the sprites used in the level file
/// Sprites to load are specified in the map properties in the level editor
/// </summary>
void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	TheSpriteManager::Instance()->loadSprite(SPRITE_PATH_PREFIX + std::string(pTextureRoot->Attribute("value")), pTextureRoot->Attribute("name"));
}

/// <summary>
/// Creates all the tilesets used in the level file
/// Tilesets to load are specified in the level editor
/// </summary>
void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	// Load the tileset (the filepath is the same as the .tmx file path)
	TheSpriteManager::Instance()->loadSprite(TILESET_PATH_PREFIX + std::string(pTilesetRoot->FirstChildElement()->Attribute("source")), pTilesetRoot->Attribute("name"));

	// Create a tileset object and fill it out
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");

	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}
