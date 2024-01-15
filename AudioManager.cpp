#include "AudioManager.h"

static bool setup = false;
static ISoundEngine* engine; // This is the core component of the audioManager. It actually makes the sounds play, pause or stop.
static ISound* sound; // Allows you to keep track of a specific audio clip. Then you can pause it etc.

void AudioManager::PlayMusic(std::string Track)
{
	if (!setup)
		Setup();

	engine->play2D(Track.c_str(), true); // Play and loop
}

// Plays the desired track.
void AudioManager::PlaySFX(std::string Track)
{
	if (!setup)
		Setup();

	if (sound) 
	{
		if (sound->getIsPaused())
			sound->setIsPaused(false);
	}
	else
		sound = engine->play2D(Track.c_str(),true, false, true); // Play and loop
}

// Stops the desired track. (Currently pauses it due to it being more efficient)
void AudioManager::StopSFX()
{
	if (sound)
		sound->setIsPaused(true);
}

// Cleans up memory when finished.
void AudioManager::Delete()
{
	engine->drop(); // Delete audio engine 
}

void AudioManager::Setup()
{
	engine = createIrrKlangDevice();
	if (!engine) {
		std::cout << " Failed to create sound engine " << std::endl;
	}
	setup = true;
}
