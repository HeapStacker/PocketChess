#include "ImageLoader.h"

SDL_Renderer* ImageLoader::renderer = nullptr;

void ImageLoader::SetTexture(SDL_Rect* sr, const char* path)
{
	srcRect = sr;
	try
	{
		if (!srcRect)
			throw "The adres of passed src_rect is not the new one.\n";
		if (!path)
			throw "The file path is not acquired.\n";
		surface = IMG_Load(path);
		if (surface == nullptr) {
			throw "Couldnt create the surface for the object.\n";
		}
		texture = SDL_CreateTextureFromSurface(ImageLoader::renderer, surface);
		if (texture == nullptr) {
			throw "Couldn't create the texture.\n";
		}
		SDL_FreeSurface(surface);
	}
	catch (const std::string& ex) {
		std::cerr << ex << std::endl;
	}
}

SDL_Texture* ImageLoader::setReturnTexture(SDL_Rect* sr, const char* path)
{
	srcRect = sr;
	try
	{
		if (!srcRect)
			throw "The adres of passed src_rect is not right.\n";
		if (!path)
			throw "The file path is not acquired.\n";
		surface = IMG_Load(path);
		if (surface == nullptr) {
			throw "Couldnt create the surface for the object.\n";
		}
		texture = SDL_CreateTextureFromSurface(ImageLoader::renderer, surface);
		if (texture == nullptr) {
			throw "Couldn't create the texture.\n";
		}
		SDL_FreeSurface(surface);
	}
	catch (const std::string& ex) {
		std::cerr << ex << std::endl;
	}
	return texture;
}

ImageLoader::~ImageLoader()
{
	std::cout << "Texture destroyed.\n";
	SDL_DestroyTexture(texture);
}

void ImageLoader::DrawTheObject(SDL_Rect* dr, SDL_Rect* sr)
{
	SDL_RenderCopy(ImageLoader::renderer, texture, sr, dr);
}


