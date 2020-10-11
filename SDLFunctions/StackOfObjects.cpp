#include "StackOfObjects.h"


void Start_Button::changeImage()
{
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->y = 20;
			if (Events::LmbPressed)
				action();
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
}

void Start_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (*Objects::windowWidth / 2) - 50;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (*Objects::windowHeight / 2) - 30;
	}
}


void Options_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (*Objects::windowWidth / 2) - 40;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (*Objects::windowHeight / 2) - 5;
	}
}

void Quit_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (*Objects::windowWidth / 2) - 40;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (*Objects::windowHeight / 2) + 10;
	}
}

void SinglePlayer_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (*Objects::windowWidth / 2) - 40;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (*Objects::windowHeight / 2) - 30;
	}
}

void Versus_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (*Objects::windowWidth / 2) - 40;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (*Objects::windowHeight / 2) - 5;
	}
}

void MultyPlayer_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (*Objects::windowWidth / 2) - 40;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (*Objects::windowHeight / 2) + 20;
	}
}

void Back_Button::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = *Objects::windowWidth - 100;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = *Objects::windowHeight - 40;
	}
}

void chessPieces::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = (Objects::boardBlockSize->w / 2 - destRect->w / 2) + thisChesPos.x * Objects::boardBlockSize->w;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = (Objects::boardBlockSize->h / 2 - destRect->h / 2) + thisChesPos.y * Objects::boardBlockSize->h;
	}
}

void chessPieces::setState()
{
	if (chessPieces::positions != chessPieces::previousPositions) {
		if (movingState) {
			std::cout << std::endl;
			std::cout << "White move.\n\n";
			movingState = false;
		}
		else {
			std::cout << std::endl;
			std::cout << "Black move.\n\n";
			movingState = true;
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				chessPieces::previousPositions[i][j] = chessPieces::positions[i][j];
			}
		}
	}
}

void chessPieces::calculateChesPieceLocation()
{
	int measureX = (*Objects::windowWidth - 200) / 8;
	int measureY = *Objects::windowHeight / 8;
	chessPieces::positions[thisChesPos.y][thisChesPos.x] = 0;
	thisChesPos.x = destRect->x / measureX;
	thisChesPos.y = destRect->y / measureY;
	if (crni) {
		chessPieces::positions[thisChesPos.y][thisChesPos.x] = 1;
	}
	if (bijeli)
		chessPieces::positions[thisChesPos.y][thisChesPos.x] = 2;
}

int chessPieces::positions[8][8]{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

int chessPieces::previousPositions[8][8]{
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2
};

bool chessPieces::movingState = true;
std::vector<chessPieces*> chessPieces::vecOfObs;

void statusBoard::changePosition()
{
	SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
	if (Objects::initWindowWidth != *Objects::windowWidth) {
		destRect->x = *Objects::windowWidth - 220;
	}
	if (Objects::initWindowHeight != *Objects::windowHeight) {
		destRect->y = 0;
		//change size
		destRect->h = *Objects::windowHeight;
	}
}
