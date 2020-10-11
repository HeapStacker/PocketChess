#include "SoundSystem.h"

int SoundSystem::currChanel = 0;
HWND SoundSystem::myConsole = GetConsoleWindow();
SoundSystem::SoundSystem() 
{
	currChanel++;
}

void SoundSystem::createTrack(const std::string& path)
{
	track = Mix_LoadMUS(path.c_str());
	if (track == nullptr) {
		ShowWindow(myConsole, SW_SHOW);
		std::cerr << "Couldn't load the audio file.\n";
	}
}

void SoundSystem::createSound(const std::string& path)
{
	sound = Mix_LoadWAV(path.c_str());
	if (sound == nullptr) {
		ShowWindow(myConsole, SW_SHOW);
		std::cerr << "Couldn't load the audio file.\n";
	}
}

void SoundSystem::playTrack(int numOfTimes)
{
	if (track != nullptr) {
		Mix_PlayMusic(track, numOfTimes);
	}
	else {
		ShowWindow(myConsole, SW_SHOW);
		std::cerr << "SDL_Music is not initialised.\n";
	}
}

void SoundSystem::pauseTrack()
{
	if (Mix_PlayingMusic()) {
		Mix_PauseMusic();
	}
	else {
		ShowWindow(myConsole, SW_SHOW);
		std::cerr << "There is nothing to pause.\n";
	}
}

void SoundSystem::stopTrack()
{
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
	else {
		ShowWindow(myConsole, SW_SHOW);
		std::cerr << "There is nothing to stop.\n";
	}
}

void SoundSystem::playSound(int numOfTimes)
{
	if (sound != nullptr) {
		Mix_PlayChannel(currChanel, sound, numOfTimes);
	}
	else {
		ShowWindow(myConsole, SW_SHOW);
		std::cerr << "There is no sound.\n";
	}
}

SoundSystem::~SoundSystem()
{
	if (track != nullptr) {
		Mix_FreeMusic(track);
	}
	if (sound != nullptr) {
		Mix_FreeChunk(sound);
	}
}
