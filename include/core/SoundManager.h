#pragma once

#include "SDL2_mixer/SDL_mixer.h"

#define ALIEN_BOSS_CHANNEL 3

/// <summary>
/// Encapsulates the Mix_Chunk SDL object
/// </summary>
class SoundEffectObject
{
public:
	SoundEffectObject(Mix_Chunk* createdMixChunk, int8_t channel = -1)
		: m_sfx(createdMixChunk), m_channel(channel)
	{
	}
	~SoundEffectObject()
	{
		Mix_FreeChunk(m_sfx);
	}

	Mix_Chunk*	getSfxChunk() const { return m_sfx; }
	int8_t		getChannel() const { return m_channel; }

private:
	Mix_Chunk*	m_sfx; // Mix_Chunk used for sound effects only
	int8_t		m_channel;
};

/// <summary>
/// Encapsulates the Mix_Music SDL object
/// </summary>
class MusicObject
{
public:
	MusicObject(Mix_Music* createdMixMusic)
		: m_music(createdMixMusic)
	{
	}
	~MusicObject()
	{
		Mix_FreeMusic(m_music);
	}

	Mix_Music*	getMusicChunk() const { return m_music; }

private:
	Mix_Music*	m_music; // Mix_music used for music only
};


/// <summary>
/// Encapsulates the audio for the program, providing utility functions to use it
/// .ogg for music and .wav for sound effects
/// </summary>
class SoundManager
{
public:
	bool init();
	void clean();

	bool loadSound(const std::string& filepath, const std::string& id, int8_t chosenChannel = -1);
	bool loadMusic(const std::string& filepath, const std::string& id);

	void playSound(const std::string& id, bool loop = false);
	void playMusic(const std::string& id, bool loop = false);

	void stopSound(int8_t channel);
	void stopAllSounds();
	void stopMusic();

	void toggleSoundEffects();
	void toggleMusic();

	bool isSoundPlaying() const { return m_bPlayingSound; }
	bool isMusicPlaying() const { return m_bPlayingMusic; }

	static SoundManager* Instance() // Get instance
	{
		static SoundManager* s_pInstance = new SoundManager;
		return s_pInstance;
	}

private:

	std::unordered_map<std::string, std::unique_ptr<SoundEffectObject>>	m_soundEffectObjects;
	std::unordered_map<std::string, std::unique_ptr<MusicObject>>		m_musicObjects;

	bool m_bPlayingSound;
	bool m_bPlayingMusic;

	SoundManager() :m_bPlayingSound(true), m_bPlayingMusic(true) {};	// Prevent construction
	SoundManager(const SoundManager&) = delete;							// Prevent construction by copying
	SoundManager& operator=(const SoundManager&) = delete;				// Prevent assignment
	~SoundManager() {};													// Prevent unwanted destruction
};
typedef SoundManager TheSoundManager;
