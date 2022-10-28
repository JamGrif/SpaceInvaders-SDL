#pragma once

#include "SDL2_ttf/SDL_ttf.h" // Required include for TTF_Font

typedef uint8_t FONT_SIZE;

/// <summary>
/// Encapsulates the TTF_Font SDL object
/// </summary>
class FontData
{
public:
	FontData(TTF_Font* pCreatedFont, uint8_t fontSize)
		:m_pFont(pCreatedFont), m_fontSize(fontSize)
	{
	}
	~FontData()
	{
		TTF_CloseFont(m_pFont);
	}

	const TTF_Font*	getTTF_Font() const { return m_pFont; }

private:
	TTF_Font*	m_pFont;
	uint8_t		m_fontSize;
};

/// <summary>
/// Encapsulates the SDL TTF library, allowing loading and usage of TTF_Font objects
/// </summary>
class TextManager
{
public:
	bool					init();
	void					clean();

	std::weak_ptr<FontData>	getFont(uint8_t textSize);

	static TextManager*		Instance() // Get instance
	{
		static TextManager* s_pInstance = new TextManager;
		return s_pInstance;
	}

private:

	// Prevents reconstruction of fonts with same font size
	std::unordered_map<FONT_SIZE, std::shared_ptr<FontData>> m_loadedFonts;

	TextManager() {};										// Prevent outside construction
	TextManager(const TextManager&) = delete;				// Prevent construction by copying
	TextManager& operator=(const TextManager&) = delete;	// Prevent assignment
	~TextManager() {};										// Prevent outside destruction
};
typedef TextManager TheTextManager;
