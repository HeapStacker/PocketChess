#pragma once
#include <iostream>
#include "Objects.h"
#include "SDL.h"


//Main-menu obs...
class Start_Button : public Objects {
public:
	Start_Button() {
		std::cout << "Start button created.\n";
		imgl = new ImageLoader();
	}
	~Start_Button()
	{
		std::cout << "Start buton deleted.\n";
		delete imgl;
	}
	void changeImage() override;
	void changePosition() override;
	void draw() override {
		changePosition();
		changeImage();
		drawAsset();
	}
	void action() override {
		*Events::start_mode = true;
	}
};

class Options_Button : public Objects {
public:
	Options_Button() {
		std::cout << "Options button created.\n";
		imgl = new ImageLoader();
	}
	~Options_Button()
	{
		std::cout << "Options button deleted.\n";
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		action();
		drawAsset();
	}
	void action() override {
		if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w)
			if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h)
				if (Events::LmbPressed)
					std::cout << "Options dont work rn.\n";
	}
};

class Quit_Button : public Objects {
public:
	Quit_Button() {
		std::cout << "Quit button created.\n";
		imgl = new ImageLoader();
	}
	~Quit_Button()
	{
		std::cout << "Quit buton deleted.\n";
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		action();
		drawAsset();
	}
	void action() override {
		if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w)
			if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h)
				if (Events::LmbPressed)
					*Events::running_mode = false;
	}
};


//Mod-selector items...
class SinglePlayer_Button : public Objects {
public:
	SinglePlayer_Button() {
		std::cout << "SinglePlayer button created.\n";
		imgl = new ImageLoader();
	}
	~SinglePlayer_Button()
	{
		std::cout << "Singleplayer button deleted.\n";
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		action();
		drawAsset();
	}
	void action() override {
		if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w)
			if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h)
				if (Events::LmbPressed)
					std::cout << "This is for singlePlayer mode." << std::endl;
	}
};

class Versus_Button : public Objects {
public:
	Versus_Button() {
		std::cout << "VersusMode button created.\n";
		imgl = new ImageLoader();
	}
	~Versus_Button()
	{
		std::cout << "VersusMode button deleted.\n";
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		action();
		drawAsset();
	}
	void action() override {
		if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
			if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
				if (Events::LmbPressed) {
					std::cout << "It's good\n";
					*Events::versus_mode = true;
				}
			}
		}		
	}
};

class MultyPlayer_Button : public Objects {
public:
	MultyPlayer_Button() {
		std::cout << "VersusMode button created.\n";
		imgl = new ImageLoader();
	}
	~MultyPlayer_Button()
	{
		std::cout << "VersusMode button deleted.\n";
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		action();
		drawAsset();
	}
	void action() override {
		if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w)
			if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h)
				if (Events::LmbPressed)
					*Events::versus_mode = true;
	}
};


//BackButton
class Back_Button : public Objects {
public:
	Back_Button()
	{
		std::cout << "Back button created.\n";
		imgl = new ImageLoader();
	}
	~Back_Button()
	{
		std::cout << "Back button deleted\n";
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		action();
		drawAsset();
	}
	void action() override {
		if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
			if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
				if (Events::LmbPressed) {
					*Events::running_mode = true;
					*Events::mainmenu_mode = true;
					*Events::start_mode = false;
					*Events::options_mode = false;
					*Events::versus_mode = false;
				}
			}
		}
	}
};


//Game-mode items

typedef struct chesPos {
	int x = 0;
	int y = 0;
}CHESPOS;

class chessPieces :public Objects {
protected:
	static bool movingState; //White move first
public:
	chessPieces()
	{
		std::cout << "Chess-piece added.\n";
		vecOfObs.push_back(this);
		imgl = new ImageLoader();
	}
	~chessPieces()
	{
		positions[thisChesPos.y][thisChesPos.y] = 0;
		std::cout << "Chess-piece destroyed.\n";
		delete imgl;
	}
	void setChessPosition(int xPos, int yPos) {
		thisChesPos.x = xPos;
		thisChesPos.y = yPos;
		destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
		destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
	}
	bool crni = false;
	bool bijeli = false;
	bool deleteMe = false;
	void changePosition();
	static int positions[8][8];
	static int previousPositions[8][8];
	static void setState();
	static std::vector<chessPieces*> vecOfObs;
	void calculateChesPieceLocation();
	CHESPOS thisChesPos{ 0, 1 };
};

class statusBoard : public Objects {
public:
	statusBoard()
	{
		std::cout << "Status board added\n";
		imgl = new ImageLoader();
	}
	~statusBoard()
	{
		delete imgl;
	}
	void changePosition() override;
	void draw() override {
		changePosition();
		drawAsset();
	}
};