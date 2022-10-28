#pragma once
#include "gameobjects/SDLGameObject.h"

#include "SDL2_ttf/SDL_ttf.h" // Required include for TTF_Font

class FontData;

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

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams) override;

	virtual void	drawObject() override;
	virtual void	updateObject() override;

	void			setTextCallback(std::string(*callback)()) { m_textCallback = callback; }
	uint8_t			getTextCallbackID() const { return m_textCallbackID; }

private:

	void			updateText(const std::string& newText);

	// Function pointer used to find and copy a specific value updated somewhere else in the program
	std::string(*m_textCallback)(); 

	// ID of function used to determine what text to copy (ID set in level editor)
	uint8_t			m_textCallbackID;

	// The actual text this object will render
	std::string		m_text;

	// Font object this object will use when rendering text
	std::weak_ptr<FontData> m_thisFont;

	SDL_Color		m_textColor;
};

class TextObjectCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<TextObject>();
	}
};
