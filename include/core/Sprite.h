#pragma once

struct SDL_Texture;
struct SDL_Rect;

class Sprite
{
public:
	Sprite(SDL_Texture* texture, const std::string& fileName, const std::string& id);
	~Sprite();

	// Determine how many sprite frames are in the sprite sheet
	void setUpIndividualSpriteDimensions(int numFrames);

	inline SDL_Texture* getTexturePtr() { return m_texture; }
	inline std::string& getFileName() { return m_fileName; }
	inline std::string& getID() { return m_id; }

	const SDL_Rect* getTotalDimensions();
	const SDL_Rect* getIndividualDimensions();

private:

	SDL_Texture* m_texture;
	std::string m_fileName;
	std::string m_id;

	SDL_Rect* m_indivdualSpriteDimension;
	SDL_Rect* m_totalSpriteDimensions;
};
