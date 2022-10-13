#pragma once

#include "SDL2_ttf/SDL_ttf.h" // Required include for TTF_Font

#define FONT_SIZE int

/// <summary>
/// Encapsulates the SDL TTF library, allowing loading and usage of TTF_Font objects
/// </summary>
class TextManager
{
public:
	bool		init();
	void		clean();

	TTF_Font*	getFont(int textSize);

	static TextManager* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new TextManager();
		return s_pInstance;
	}

private:
	static TextManager* s_pInstance;

	// Prevents reconstruction of fonts with same font size
	std::unordered_map<FONT_SIZE, TTF_Font*> m_loadedFonts;

	TextManager() {};								// Prevent construction
	TextManager(const TextManager&) {};				// Prevent construction by copying
	TextManager& operator=(const TextManager&) {};	// Prevent assignment
	~TextManager() {};								// Prevent unwanted destruction

};
typedef TextManager TheTextManager;
