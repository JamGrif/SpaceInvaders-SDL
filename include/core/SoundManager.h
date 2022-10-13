#pragma once

struct Mix_Chunk;
struct _Mix_Music;
typedef struct _Mix_Music Mix_Music; // Defined in SDL_mixer.h

/// <summary>
/// Encapsulates the audio for the program, providing utility functions to use it
/// .ogg for music and .wav for sound effects
/// </summary>
class SoundManager
{
public:
	bool init();
	void clean();

	bool loadSound(const std::string& filepath, const std::string& id);
	bool loadMusic(const std::string& filepath, const std::string& id);

	void playSound(const std::string& id, int loop = false);
	void playMusic(const std::string& id, int loop = false);

	void toggleSoundEffects();
	void toggleMusic();

	bool isSoundPlaying() const { return m_bPlayingSound; }

	bool isMusicPlaying() const { return m_bPlayingMusic; }

	static SoundManager* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new SoundManager();
		return s_pInstance;
	}

private:
	static SoundManager* s_pInstance; 

	std::unordered_map<std::string, Mix_Chunk*> m_sfxs;		// Mix_Chunk used for sound effects only
	std::unordered_map<std::string, Mix_Music*> m_music;	// Mix_Music used for music tracks only

	bool m_bPlayingSound;
	bool m_bPlayingMusic;

	SoundManager() :m_bPlayingSound(true), m_bPlayingMusic(true) {};					// Prevent construction
	SoundManager(const SoundManager&) :m_bPlayingSound(true), m_bPlayingMusic(true) {};	// Prevent construction by copying
	SoundManager& operator=(const SoundManager&) {};									// Prevent assignment
	~SoundManager() {};																	// Prevent unwanted destruction
};
typedef SoundManager TheSoundManager;
