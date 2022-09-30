#pragma once

#include "SDL2_mixer/SDL_mixer.h"

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

// .ogg for music | .wav for sound effects
class SoundManager
{
public:
	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, sound_type type);

	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);

private:
	static SoundManager* s_pInstance; // Singleton as there should only be one place the sounds are stored and should be accessible from anywhere in the game

	std::map<std::string, Mix_Chunk*> m_sfxs;	// Mix_Chunk used for sound effects only
	std::map<std::string, Mix_Music*> m_music;	// Mix_Music used for music tracks only

	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&);
	SoundManager& operator= (const SoundManager&);

};

