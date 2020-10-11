#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "SDL.h"
#include "SDL_image.h"
//#include "EventChecker.h"

class ImageLoader {
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect* srcRect = nullptr;   //For the whole image
	SDL_Rect* destRect = nullptr;
public:
	static SDL_Renderer* renderer;
	ImageLoader() {}
	void SetTexture(SDL_Rect* sr, const char* path); //If animationCount == 1 it has 2 animations, if 0 it has none
	SDL_Texture* setReturnTexture(SDL_Rect* sr, const char* path);
	void DrawTheObject(SDL_Rect* dr, SDL_Rect* sr);
	~ImageLoader();
};


