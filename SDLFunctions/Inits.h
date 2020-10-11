#pragma once
#include <iostream>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <Windows.h>

#define PROBLEM_DETECTION();\
showCMD();\
ErrorMess();\
ReturnValue();\

HWND console = GetConsoleWindow();
inline void removeCMD() {
	ShowWindow(console, SW_HIDE);
}
inline void showCMD() {
	ShowWindow(console, SW_SHOW);
}
inline void ErrorMess() {
	std::cout << SDL_GetError() << std::endl;
	std::cout << IMG_GetError() << std::endl;
	std::cout << Mix_GetError() << std::endl;
}
inline int ReturnValue() {
	return 0;
}

int windowWidth = 800;
int windowHeight = 600;

SDL_Window* window = nullptr; 
SDL_Event event;
SDL_Renderer* renderer = nullptr;
constexpr int FramesPerSecond = 60;
bool swtch = true;
//GameStates
bool running = true;
bool mmmod = true;
bool options = false;
bool modsell = false;
bool versus = false;

//Game objs...
int drawForX = 0;
int drawForY = 0;
SDL_Rect rect;
SDL_Rect mouse;
SDL_Rect mouseDr;
constexpr int mouseSize = 21;
SDL_Rect backgroundSr{ 0, 0, 32, 32 }, backgroundDr{ 0, 0, 32, 32 };
SDL_Rect startButtonSr{ 0, 0, 100, 20 }, startButtonDr{ windowWidth / 2 - 50, windowHeight / 2 - 30, 100, 20 };
SDL_Rect optionsButtonSr{ 0, 0, 80, 18 }, optionsButtonDr{ windowWidth / 2 - 40, windowHeight / 2 - 5, 80, 18 };
SDL_Rect quitButtonSr{ 0, 0, 80, 18 }, quitButtonDr{ windowWidth / 2 - 40, windowHeight / 2 + 10, 80, 18 };
SDL_Rect singleplayerButtonSr{ 0, 0, 80, 18 }, singleplayerButtonDr{ windowWidth / 2 - 40, windowHeight / 2 - 30, 80, 18 };
SDL_Rect versusButtonSr{ 0, 0, 80, 18 }, versusButtonDr{ windowWidth / 2 - 40, windowHeight / 2 - 5, 80, 18 };
SDL_Rect multyplayerSr{ 0, 0, 80, 18 }, multyplayerDr{ windowWidth / 2 - 40, windowHeight / 2 + 20, 80, 18 };
SDL_Rect bButtonSr{ 0, 0, 50, 15 }, bButtonDr{ windowWidth - 100, windowHeight - 40, 50, 15 };
SDL_Rect whiteBoardPieceSr{ 0, 0, 75, 75 }, whiteBoardPieceDr{ 0, 0, 75, 75 };
SDL_Rect blackBoardPieceSr{ 0, 0, 75, 75 }, blackBoardPieceDr{ 0, 0, 75, 75 };
SDL_Rect blackPijunSr1{ 0, 0, 64, 64 }, blackPijunDr1{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr2{ 0, 0, 64, 64 }, blackPijunDr2{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr3{ 0, 0, 64, 64 }, blackPijunDr3{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr4{ 0, 0, 64, 64 }, blackPijunDr4{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr5{ 0, 0, 64, 64 }, blackPijunDr5{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr6{ 0, 0, 64, 64 }, blackPijunDr6{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr7{ 0, 0, 64, 64 }, blackPijunDr7{ 0, 0, 64, 64 };
SDL_Rect blackPijunSr8{ 0, 0, 64, 64 }, blackPijunDr8{ 0, 0, 64, 64 };
SDL_Rect blackCastleLSr{ 0, 0, 64, 64 }, blackCastleLDr{ 0, 0, 64, 64 };
SDL_Rect blackCastleRSr{ 0, 0, 64, 64 }, blackCastleRDr{ 0, 0, 64, 64 };
SDL_Rect blackHorseLSr{ 0, 0, 64, 64 }, blackHorseLDr{ 0, 0, 64, 64 };
SDL_Rect blackHorseRSr{ 0, 0, 64, 64 }, blackHorseRDr{ 0, 0, 64, 64 };
SDL_Rect blackHunterLSr{ 0, 0, 64, 64 }, blackHunterLDr{ 0, 0, 64, 64 };
SDL_Rect blackHunterRSr{ 0, 0, 64, 64 }, blackHunterRDr{ 0, 0, 64, 64 };
SDL_Rect blackKingSr{ 0, 0, 64, 64 }, blackKingDr{ 0, 0, 64, 64 };
SDL_Rect blackQuinSr{ 0, 0, 64, 64 }, blackQuinDr{ 0, 0, 64, 64 };

SDL_Rect whitePijunSr1{ 0, 0, 64, 64 }, whitePijunDr1{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr2{ 0, 0, 64, 64 }, whitePijunDr2{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr3{ 0, 0, 64, 64 }, whitePijunDr3{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr4{ 0, 0, 64, 64 }, whitePijunDr4{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr5{ 0, 0, 64, 64 }, whitePijunDr5{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr6{ 0, 0, 64, 64 }, whitePijunDr6{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr7{ 0, 0, 64, 64 }, whitePijunDr7{ 0, 0, 64, 64 };
SDL_Rect whitePijunSr8{ 0, 0, 64, 64 }, whitePijunDr8{ 0, 0, 64, 64 };
SDL_Rect whiteCastleLSr{ 0, 0, 64, 64 }, whiteCastleLDr{ 0, 0, 64, 64 };
SDL_Rect whiteCastleRSr{ 0, 0, 64, 64 }, whiteCastleRDr{ 0, 0, 64, 64 };
SDL_Rect whiteHorseLSr{ 0, 0, 64, 64 }, whiteHorseLDr{ 0, 0, 64, 64 };
SDL_Rect whiteHorseRSr{ 0, 0, 64, 64 }, whiteHorseRDr{ 0, 0, 64, 64 };
SDL_Rect whiteHunterLSr{ 0, 0, 64, 64 }, whiteHunterLDr{ 0, 0, 64, 64 };
SDL_Rect whiteHunterRSr{ 0, 0, 64, 64 }, whiteHunterRDr{ 0, 0, 64, 64 };
SDL_Rect whiteKingSr{ 0, 0, 64, 64 }, whiteKingDr{ 0, 0, 64, 64 };
SDL_Rect whiteQuinSr{ 0, 0, 64, 64 }, whiteQuinDr{ 0, 0, 64, 64 };
SDL_Rect boardWithStatsSr{ 0, 0, 200, windowHeight };
SDL_Rect boardWithStatsDr{ windowWidth - 220, 0, 230, windowHeight };







