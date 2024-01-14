#include "AudioManager.h"

static bool setup = false;
static ISoundEngine* engine;
static ISound* sound;
void AudioManager::PlayMusic(std::string Track)
{
	if (!setup)
		Setup();

	engine->play2D(Track.c_str(), true); // Play and loop
}

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

void AudioManager::StopSFX()
{
	if (sound)
		sound->setIsPaused(true);
}

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
