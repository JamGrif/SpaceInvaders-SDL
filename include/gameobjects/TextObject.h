#pragma once
#include "SDLGameObject.h"

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

class TextObject :
    public SDLGameObject
{
public:
	TextObject();
	~TextObject();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

	void setTextCallback(std::string(*callback)()) { m_textCallback = callback; }
	int getTextCallbackID() const { return m_textCallbackID; }

private:

	std::string(*m_textCallback)(); // function pointer to store what function will run when the button is clicked on
	int m_textCallbackID;

	void updateText(const std::string& newText);
	//void updateText(int newText);

	std::string m_text;
	int m_textSize;

	TTF_Font* m_thisFont;

	SDL_Texture* m_textTexture;

	SDL_Rect m_textDimensions;
	SDL_Color m_textColor = { 0, 255, 0 };

};

class TextObjectCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new TextObject();
	}
};
