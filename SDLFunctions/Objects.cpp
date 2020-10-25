#include "Objects.h"
#include <ctime>

SDL_Window* Objects::window = nullptr;
SDL_Renderer* Objects::renderer = nullptr;
int Objects::initWindowWidth = 0;
int Objects::initWindowHeight = 0;
int* Objects::windowWidth = nullptr;
int* Objects::windowHeight = nullptr;
SDL_Rect* Objects::boardBlockSize = nullptr;
SDL_Rect Objects::replacementBlockSr{ 0, 0, 75, 75 }, Objects::replacementBlockDr{ 0, 0, 75, 75 };
SDL_Rect Objects::redBlockInstanceSr{ 0, 0, 75, 75 }, Objects::redBlockInstanceDr{ 0, 0, 75, 75 };
ImageLoader Objects::theReplacementBlockInstance;
ImageLoader Objects::redEatingBlockInstance;

void Objects::createReplacementBlockClass()
{
	Objects::theReplacementBlockInstance = ImageLoader();
	Objects::theReplacementBlockInstance.SetTexture(&Objects::replacementBlockSr, "Assets/HighLightedBoardPiece.png");
}

void Objects::createRedEatingBlockInstance() {
	Objects::redEatingBlockInstance = ImageLoader();
	Objects::redEatingBlockInstance.SetTexture(&Objects::redBlockInstanceSr, "Assets/RedEatingBlock.png");
}

void Objects::loadAssets(SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	srcRect = sr;
	destRect = dr;
	thisObjTexture = imgl->setReturnTexture(sr, path);
}

void Objects::drawAsset()
{
	imgl->DrawTheObject(destRect, srcRect);
}


