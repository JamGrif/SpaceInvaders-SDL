#pragma once

#include "tinyxml.h"

class GameObject;

class StateParser
{
public:
	// Takes the filename of the xml file, the current stateID value and a pointer to std::vector of GameObjects for that state
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);

private:
	void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects);
	void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};

