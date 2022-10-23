#pragma once
#include "gameobjects/SDLGameObject.h"

#include "SDL2_ttf/SDL_ttf.h" // Required include for TTF_Font

/// <summary>
/// Text object that can appear in the game
/// Can optionally copy values by setting a text callback id in level editor and in OnEnterState of state used in
/// Uses SDL_ttf to draw text to the screen
/// </summary>
class TextObject :
    public SDLGameObject
{
public:
	TextObject();
	~TextObject();

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams);

	virtual void	drawObject();
	virtual void	updateObject();

	void			setTextCallback(std::string(*callback)()) { m_textCallback = callback; }
	uint8_t			getTextCallbackID() const { return m_textCallbackID; }

private:
	void updateText(const std::string& newText);

	// Function pointer used to find and copy a specific value updated somewhere else in the program
	std::string(*m_textCallback)(); 

	//ID of function used to determine what text to copy (ID set in level editor)
	uint8_t m_textCallbackID;

	// The actual text this object will render
	std::string m_text;

	// Font object this object will use when rendering text
	TTF_Font* m_thisFont;

	SDL_Texture* m_textTexture;

	// Dimension of the square the text is rendered too, updated each time the text is changed
	SDL_Rect m_textDimensions;

	SDL_Color m_textColor;
};

class TextObjectCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<TextObject>();
	}
};
