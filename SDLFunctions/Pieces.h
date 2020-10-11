#pragma once
#include "StackOfObjects.h"
#include<thread>

class CrniPijun :public chessPieces
{
	bool delOp = false;
	bool it_Moved = false;
	void seeIfItMoved();
	int xInitChesPos = 0;
	int yInitChesPos = 0;
public:
	CrniPijun(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~CrniPijun()
	{
	}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 2) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obrirsi bijeloga.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class CrnaKula :public chessPieces {
	bool hpl = false;
	bool hmin = false;
	bool vpl = false;
	bool vmin = false;
	int a = 1, b = 1, c = 1, d = 1;
public:
	CrnaKula(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~CrnaKula(){}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 2) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obrirsi bijeloga.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class CrniLovac :public chessPieces {
	bool RightDown = false;
	bool RightUp = false;
	bool LeftDown = false;
	bool LeftUp = false;
	int RD = 1, RU = 1, LD = 1, LU = 1;
	int pointerInt = 0;
public:
	CrniLovac(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~CrniLovac() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action() ;
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 2) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obrirsi bijeloga.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class CrnaKraljica :public chessPieces {
	bool hpl = false;
	bool hmin = false;
	bool vpl = false;
	bool vmin = false;
	bool RightDown = false;
	bool RightUp = false;
	bool LeftDown = false;
	bool LeftUp = false;
	int a = 1, b = 1, c = 1, d = 1;
	int RD = 1, RU = 1, LD = 1, LU = 1;
	int pointerInt = 0;
public:
	CrnaKraljica(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~CrnaKraljica() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action() ;
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 2) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obrirsi bijeloga.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class CrniKralj :public chessPieces {
	bool atacked = false;
public:
	CrniKralj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~CrniKralj() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action() ;
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 2) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obrirsi bijeloga.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class CrniKonj :public chessPieces {
public:
	CrniKonj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~CrniKonj() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action() ;
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 2) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obrirsi bijeloga.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class BijeliPijun :public chessPieces {
	bool it_Moved = false;
	void seeIfItMoved();
	int xInitChesPos = 0;
	int yInitChesPos = 0;
public:
	BijeliPijun(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~BijeliPijun() {
	}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action() ;
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 1){
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obriri crnog.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class BijelaKula :public chessPieces {
	bool hpl = false;
	bool hmin = false;
	bool vpl = false;
	bool vmin = false;
	int a = 1, b = 1, c = 1, d = 1;
public:
	BijelaKula(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~BijelaKula() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 1) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obriri crnog.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class BijeliLovac :public chessPieces {
	bool RightDown = false;
	bool RightUp = false;
	bool LeftDown = false;
	bool LeftUp = false;
	int RD = 1, RU = 1, LD = 1, LU = 1;
	int pointerInt = 0;
public:
	BijeliLovac(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~BijeliLovac() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 1) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obriri crnog.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class BijelaKraljica :public chessPieces {
	bool hpl = false;
	bool hmin = false;
	bool vpl = false;
	bool vmin = false;
	bool RightDown = false;
	bool RightUp = false;
	bool LeftDown = false;
	bool LeftUp = false;
	int a = 1, b = 1, c = 1, d = 1;
	int RD = 1, RU = 1, LD = 1, LU = 1;
	int pointerInt = 0;
public:
	BijelaKraljica(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~BijelaKraljica() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 1) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obriri crnog.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class BijeliKralj :public chessPieces {
	bool atacked = false;
public:
	BijeliKralj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~BijeliKralj() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 1) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obriri crnog.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};

class BijeliKonj :public chessPieces {
public:
	BijeliKonj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path);
	~BijeliKonj() {}
	void draw() {
		changePosition();
		action();
		drawAsset();
	}
	void action();
	void setExistance() {
		if (chessPieces::previousPositions[thisChesPos.y][thisChesPos.x] == 1) {
			for (chessPieces* cp : vecOfObs) {
				if (thisChesPos.x == cp->thisChesPos.x && thisChesPos.y == cp->thisChesPos.y) {
					std::cout << "Obriri crnog.\n";
					cp->deleteMe = true;
					deleteMe = false;
				}
			}
		}
	}
};