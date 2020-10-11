#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "SDL_mixer.h"
class SoundSystem
{
	Mix_Music* track = nullptr; //For audio longer than 10s
	Mix_Chunk* sound = nullptr;//For sounds less than 10s (Mix_LoadWAv())
public:
	static HWND myConsole;
	static int currChanel;
	SoundSystem();
	void createTrack(const std::string& path);
	void createSound(const std::string& path);
	void playTrack(int numOfTimes); //if numOFTimes = -1 it will play for eternity
	void pauseTrack();
	void stopTrack();

	void playSound(int numOfTimes); //if numOFTimes = -1 it will play for eternity
	//void stopSound();

	~SoundSystem();
};

