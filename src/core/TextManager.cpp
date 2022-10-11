#include "pch.h"
#include "core/TextManager.h"

#include "SDL2/SDL.h"

#define INITIALIZE_SUCCESS 0
#define FONTPATH "res/text/04B_30__.ttf"

TextManager* TextManager::s_pInstance = nullptr;

bool TextManager::init()
{
	if (TTF_Init() != INITIALIZE_SUCCESS)
	{
		std::cout << "TTF could not initialize - " << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}


void TextManager::clean()
{
	// Loop through and delete all open fonts
	for (auto font : m_loadedFonts)
	{
		TTF_CloseFont(font.second);
	}

	TTF_Quit();
}


TTF_Font* TextManager::getFont(int textSize)
{
	// If font of size textSize doesn't already exist, create it, add it to map and return it
	if (!m_loadedFonts.count(textSize))
	{
		TTF_Font* temp = TTF_OpenFont(FONTPATH, textSize);
		m_loadedFonts.insert({ textSize, temp });
		return temp;
	}

	// Font does exist of textSize so return it
	return m_loadedFonts.at(textSize);
}


