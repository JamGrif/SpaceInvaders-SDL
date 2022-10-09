#include "pch.h"
#include "level/LevelParser.h"

#include "level/Level.h"
#include "core/SpriteManager.h"

#include "level/TileLayer.h"
#include "level/ObjectLayer.h"
#include "gameobjects/BaseGameObject.h"
#include "gameobjects/Alien.h"
#include "gameobjects/Player.h"
#include "gameobjects/PlayerLives.h"
#include "gameobjects/AlienBoss.h"

#include "Base64/base64.h"
#include "zlib/zlib.h"
#include "tinyXML/tinyxml.h"


Level* LevelParser::parseLevel(const char* levelFile)
{
	// Create the TinyXML document and load the map XML
	TiXmlDocument levelDocument;

	std::string filepath = "res/levels/" + std::string(levelFile);

	if (!levelDocument.LoadFile(filepath))
	{
		std::cout << "Couldn't find document at filepath: " << filepath << std::endl;
		std::cout << levelDocument.ErrorDesc() << std::endl;
	}

	// Create the level object
	Level* pLevel = new Level();

	// Get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	//int m_tileSize;
	//int m_width;
	//int m_height;

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

	
	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	std::string tilesetFilepath = "res/levels/" + std::string(pTilesetRoot->FirstChildElement()->Attribute("source"));

	TheSpriteManager::Instance()->loadSprite(tilesetFilepath, pTilesetRoot->Attribute("name"));

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

// The tile IDs are compressed and encoded in the .tmx file.
// Uses the Base64 and zlib libraries to help decode and decompress the data
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

// Gets the texture name and value from file and adds to TextureManager
void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	std::string textureFilepath = "res/sprites/" + std::string(pTextureRoot->Attribute("value"));
	TheSpriteManager::Instance()->loadSprite(textureFilepath, pTextureRoot->Attribute("name"));
}


void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<BaseLayer*>* pLayers)
{
	// Create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();

	//std::cout << pObjectElement->FirstChildElement()->Value() << std::endl;;

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() != std::string("object"))
			continue;
		
		//std::cout << e->Attribute("class") << std::endl;

		// Check if type exists
		if (!TheGameObjectFactory::Instance()->checkIfExist(e->Attribute("class")))
		{
			std::cout << "Could not create object of type: " << e->Attribute("class") << std::endl;
			continue;
		}

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

		BaseGameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("class"));

		// Create the object just like the state parser
		pGameObject->loadObject(tempLoaderParams);

		// If the object is an Alien then put it in a separate vector, otherwise put it in the normal vector
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

			if (dynamic_cast<AlienBoss*>(pGameObject))
				pObjectLayer->setAlienBoss(dynamic_cast<AlienBoss*>(pGameObject));
		}
		
	}


	// Once loaded all the objects for this layer, we can push it into our level layer array
	pLayers->push_back(pObjectLayer);
}
