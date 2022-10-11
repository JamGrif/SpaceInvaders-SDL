#pragma once

// Forward Declarations
struct Mix_Chunk;
struct _Mix_Music;
typedef struct _Mix_Music Mix_Music; // Defined in SDL_mixer.h

// .ogg for music | .wav for sound effects
class SoundManager
{
public:
	bool init();
	void clean();

	bool loadSound(const std::string& fileName, const std::string& id);
	bool loadMusic(const std::string& fileName, const std::string& id);

	void playSound(const std::string& id, int loop = false);
	void playMusic(const std::string& id, int loop = false);

	void toggleSound();
	void toggleMusic();

	bool isSoundPlaying() const { return m_bPlayingSound; }

	bool isMusicPlaying() const { return m_bPlayingMusic; }

	static SoundManager* Instance() // Instance Get
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
