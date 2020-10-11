#pragma once
#include "SDL.h"
#include "ImageLoader.h"
#include "Events.h"
#include <assert.h>


class Objects
{	
protected:
	SDL_Rect* srcRect = nullptr;
	SDL_Rect* destRect = nullptr;
	SDL_Texture* thisObjTexture = nullptr;
	ImageLoader* imgl = nullptr;
	void drawAsset(); //draw & uppdate
	//Chess-piecess 
	bool enemySide = false;
	int piecesYouAte = 0;
	//game bools...
	bool rochade = false;
	//game-states..
	bool win = false;
	bool lose = false;
	bool path = false;
	//holding mechanics...
	bool holding = false;
	int holdingCounter = 0;
public:
	Objects() {}
	void loadAssets(SDL_Rect* sr, SDL_Rect* dr, const char* path);
	virtual ~Objects() {
	}
	virtual void changeImage() {}
	virtual void changePosition() {}
	virtual void action() {}
	virtual void draw() {}


	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static int initWindowWidth, initWindowHeight;
	static int *windowWidth, *windowHeight;

	//For manipulating mouse obj.
	static ImageLoader thisMouseObj;

	//ChessBoardBlockPieceSize...
	static SDL_Rect* boardBlockSize;

	//ReplacementBoardBlock...
	static SDL_Rect replacementBlockSr, replacementBlockDr;
	static SDL_Rect redBlockInstanceSr, redBlockInstanceDr;
	static int positions[8][8];
	static ImageLoader theReplacementBlockInstance;
	static ImageLoader redEatingBlockInstance;
	static void createReplacementBlockClass();
	static void createRedEatingBlockInstance();
};

