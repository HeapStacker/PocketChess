#include "Pieces.h"
#include <cmath>

static bool CheckIfKingIsAtacked(int posX, int posY) {
	for (chessPieces* obj : chessPieces::vecOfObs) {
		if (obj->thisChesPos.x == posX && obj->thisChesPos.y == posY)
			return true;
	}
}

void CrniPijun::seeIfItMoved()
{
	if (thisChesPos.x != xInitChesPos || thisChesPos.y != yInitChesPos)
		it_Moved = true;
}

CrniPijun::CrniPijun(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	crni = true;
	chessPieces::positions[row][column] = 1;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
	xInitChesPos = column;
	yInitChesPos = row;
}

void CrniPijun::action()
{
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (!chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						seeIfItMoved();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (!chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.w = boardBlockSize->w;
			Objects::replacementBlockDr.h = boardBlockSize->h;
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x] == 0) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > thisChesPos.y * boardBlockSize->h && Events::Return_YMousePos() < (1 + thisChesPos.y) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
					}
				}
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y + 1) * boardBlockSize->h && Events::Return_YMousePos() < (2 + thisChesPos.y) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > (thisChesPos.x + 1) * boardBlockSize->w && Events::Return_XMousePos() < (2 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y + 1) * boardBlockSize->h && Events::Return_YMousePos() < (thisChesPos.y + 2) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > (thisChesPos.x - 1) * boardBlockSize->w && Events::Return_XMousePos() < thisChesPos.x * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y + 1) * boardBlockSize->h && Events::Return_YMousePos() < (thisChesPos.y + 2) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x] == 0 && chessPieces::positions[thisChesPos.y + 2][thisChesPos.x] == 0 && !it_Moved) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > thisChesPos.y * boardBlockSize->h && Events::Return_YMousePos() < (1 + thisChesPos.y) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
					}
				}
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y + 2) * boardBlockSize->h && Events::Return_YMousePos() < (3 + thisChesPos.y) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
		}
	}
}

CrnaKula::CrnaKula(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	crni = true;
	chessPieces::positions[row][column] = 1;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void CrnaKula::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (!chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
						a = 1, b = 1, c = 1, d = 1;
						hpl = false;
						hmin = false;
						vpl = false;
						vmin = false;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (!chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.w = boardBlockSize->w;
			Objects::replacementBlockDr.h = boardBlockSize->h;
			Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
			Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
			while (!hpl) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 1 || a + thisChesPos.x > 7)
					hpl = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 2) {
					a++;
					hpl = true;
				}
				else
					a++;
			}
			while (!hmin) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 1 || thisChesPos.x - b < 0)
					hmin = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 2) {
					b++;
					hmin = true;
				}
				else
					b++;
			}
			while (!vpl) {
				if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 1 || c + thisChesPos.y > 7)
					vpl = true;
				else if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 2) {
					c++;
					vpl = true;
				}
				else
					c++;
			}
			while (!vmin) {
				if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 1 || thisChesPos.y - d < 0)
					vmin = true;
				else if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 2) {
					d++;
					vmin = true;
				}
				else
					d++;
			}
			for (int i = 0; i < a; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 2) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				if (i + thisChesPos.x < 8 && chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 0) {
					Objects::replacementBlockDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < b; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - i] == 2) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < c; i++) {
				if (chessPieces::positions[thisChesPos.y + i][thisChesPos.x] == 2) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < d; i++) {
				if (chessPieces::positions[thisChesPos.y - i][thisChesPos.x] == 2) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			int measureX = (*Objects::windowWidth - 200) / 8;
			int measureY = *Objects::windowHeight / 8;
			int showingPlaceX = Events::Return_XMousePos() / measureX;
			int showingPlaceY = Events::Return_YMousePos() / measureY;
			if (showingPlaceX < a + thisChesPos.x && showingPlaceX > thisChesPos.x - b && showingPlaceX < 8 && showingPlaceY == thisChesPos.y)
				destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
			if (showingPlaceY < c + thisChesPos.y && showingPlaceY > thisChesPos.y - d && showingPlaceX == thisChesPos.x)
				destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
		}
	}
}

CrniLovac::CrniLovac(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	crni = true;
	chessPieces::positions[row][column] = 1;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void CrniLovac::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (!chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
						RD = 1, RU = 1, LD = 1, LU = 1;
						RightDown = false;
						RightUp = false;
						LeftDown = false;
						LeftUp = false;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (!chessPieces::movingState) {
		if (holding) {
			int x = thisChesPos.x;
			int y = thisChesPos.y;
			Objects::replacementBlockDr.x = x * boardBlockSize->w;
			Objects::replacementBlockDr.y = y * boardBlockSize->h;
			Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
			for (int i = y + 1; i < 8; i++) {
				for (int j = x + 1; j < 8; j++) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							RD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = 8;
						}
						else {
							i = 8;
							j = 8;
						}
					}
				}
			}
			for (int i = y + 1; i < 8; i++) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == abs(j - x)) {
						if (chessPieces::positions[i][j] == 0) {
							LD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							LD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = -1;
						}
						else {
							i = 8;
							j = -1;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x + 1; j < 8; j++) {
					if (abs(i - y) == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							RU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = 8;
						}
						else {
							i = -1;
							j = 8;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							LU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							LU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = -1;
						}
						else {
							i = -1;
							j = -1;
						}
					}
				}
			}
			int measureX = (*Objects::windowWidth - 200) / 8;
			int measureY = *Objects::windowHeight / 8;
			int showingPlaceX = Events::Return_XMousePos() / measureX;
			int showingPlaceY = Events::Return_YMousePos() / measureY;
			if ((showingPlaceX < RD + x && showingPlaceX >= x) && (showingPlaceY < RD + y && showingPlaceY >= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX < RU + x && showingPlaceX >= x) && (showingPlaceY <= y && showingPlaceY > y - RU)) {
				if (showingPlaceX - x == abs(showingPlaceY - y) && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LD && showingPlaceX <= x) && (showingPlaceY < LD + y && showingPlaceY >= y)) {
				if (abs(showingPlaceX - x) == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LU && showingPlaceX <= x) && (showingPlaceY > y - LU && showingPlaceY <= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			RD = 1;
			RU = 1;
			LD = 1;
			LU = 1;
		}
	}
}

CrnaKraljica::CrnaKraljica(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	crni = true;
	chessPieces::positions[row][column] = 1;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void CrnaKraljica::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (!chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
						a = 1, b = 1, c = 1, d = 1;
						hpl = false;
						hmin = false;
						vpl = false;
						vmin = false;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (!chessPieces::movingState) {
		if (holding) {
			int x = thisChesPos.x;
			int y = thisChesPos.y;
			Objects::replacementBlockDr.w = boardBlockSize->w;
			Objects::replacementBlockDr.h = boardBlockSize->h;
			while (!hpl) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 1 || a + thisChesPos.x > 7)
					hpl = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 2) {
					a++;
					hpl = true;
				}
				else
					a++;
			}
			while (!hmin) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 1 || thisChesPos.x - b < 0)
					hmin = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 2) {
					b++;
					hmin = true;
				}
				else
					b++;
			}
			while (!vpl) {
				if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 1 || c + thisChesPos.y > 7)
					vpl = true;
				else if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 2) {
					c++;
					vpl = true;
				}
				else
					c++;
			}
			while (!vmin) {
				if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 1 || thisChesPos.y - d < 0)
					vmin = true;
				else if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 2) {
					d++;
					vmin = true;
				}
				else
					d++;
			}
			for (int i = 0; i < a; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 2) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				if (i + thisChesPos.x < 8 && chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 0) {
					Objects::replacementBlockDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < b; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - i] == 2) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < c; i++) {
				if (chessPieces::positions[thisChesPos.y + i][thisChesPos.x] == 2) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < d; i++) {
				if (chessPieces::positions[thisChesPos.y - i][thisChesPos.x] == 2) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = y + 1; i < 8; i++) {
				for (int j = x + 1; j < 8; j++) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							RD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = 8;
						}
						else {
							i = 8;
							j = 8;
						}
					}
				}
			}
			for (int i = y + 1; i < 8; i++) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == abs(j - x)) {
						if (chessPieces::positions[i][j] == 0) {
							LD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							LD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = -1;
						}
						else {
							i = 8;
							j = -1;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x + 1; j < 8; j++) {
					if (abs(i - y) == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							RU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = 8;
						}
						else {
							i = -1;
							j = 8;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							LU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 2) {
							LU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = -1;
						}
						else {
							i = -1;
							j = -1;
						}
					}
				}
			}
			int measureX = (*Objects::windowWidth - 200) / 8;
			int measureY = *Objects::windowHeight / 8;
			int showingPlaceX = Events::Return_XMousePos() / measureX;
			int showingPlaceY = Events::Return_YMousePos() / measureY;
			if (showingPlaceX < a + thisChesPos.x && showingPlaceX > thisChesPos.x - b && showingPlaceX < 8 && showingPlaceY == thisChesPos.y)
				destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
			if (showingPlaceY < c + thisChesPos.y && showingPlaceY > thisChesPos.y - d && showingPlaceX == thisChesPos.x)
				destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
			if ((showingPlaceX < RD + x && showingPlaceX >= x) && (showingPlaceY < RD + y && showingPlaceY >= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX < RU + x && showingPlaceX >= x) && (showingPlaceY <= y && showingPlaceY > y - RU)) {
				if (showingPlaceX - x == abs(showingPlaceY - y) && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LD && showingPlaceX <= x) && (showingPlaceY < LD + y && showingPlaceY >= y)) {
				if (abs(showingPlaceX - x) == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LU && showingPlaceX <= x) && (showingPlaceY > y - LU && showingPlaceY <= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			RD = 1;
			RU = 1;
			LD = 1;
			LU = 1;
		}
	}
}

CrniKralj::CrniKralj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	crni = true;
	chessPieces::positions[row][column] = 1;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void CrniKralj::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (!chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (!chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
			Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
			Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
			if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
				destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
				destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x + 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x - 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x] == 0) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x] == 2) {
				Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x] == 0) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x] == 2) {
				Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
		}
	}
}

CrniKonj::CrniKonj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	crni = true;
	chessPieces::positions[row][column] = 1;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void CrniKonj::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (!chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (!chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
			Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
			Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
			if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
				destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
				destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x - 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x + 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 2] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 2] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x + 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x - 1] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 2] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 2] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
		}
	}
}

void BijeliPijun::seeIfItMoved()
{
	if (thisChesPos.x != xInitChesPos || thisChesPos.y != yInitChesPos)
		it_Moved = true;
}

BijeliPijun::BijeliPijun(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	bijeli = true;
	chessPieces::positions[row][column] = 2;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
	xInitChesPos = column;
	yInitChesPos = row;
}

void BijeliPijun::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						seeIfItMoved();
						holdingCounter = 0;
						holding = false;
						setExistance();
						std::cout << std::endl;
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.w = boardBlockSize->w;
			Objects::replacementBlockDr.h = boardBlockSize->h;
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x] == 0) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > thisChesPos.y * boardBlockSize->h && Events::Return_YMousePos() < (1 + thisChesPos.y) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
					}
				}
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y - 1) * boardBlockSize->h && Events::Return_YMousePos() < thisChesPos.y * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > (thisChesPos.x - 1) * boardBlockSize->w && Events::Return_XMousePos() < thisChesPos.x * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y - 1) * boardBlockSize->h && Events::Return_YMousePos() < thisChesPos.y * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > (thisChesPos.x + 1) * boardBlockSize->w && Events::Return_XMousePos() < (thisChesPos.x + 2) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y - 1) * boardBlockSize->h && Events::Return_YMousePos() < thisChesPos.y * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x] == 0 && chessPieces::positions[thisChesPos.y - 2][thisChesPos.x] == 0 && !it_Moved) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y - 2) * boardBlockSize->h && Events::Return_YMousePos() < (thisChesPos.y - 1) * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
				if (Events::Return_XMousePos() > thisChesPos.x * boardBlockSize->w && Events::Return_XMousePos() < (1 + thisChesPos.x) * boardBlockSize->w) {
					if (Events::Return_YMousePos() > (thisChesPos.y - 1) * boardBlockSize->h && Events::Return_YMousePos() < thisChesPos.y * boardBlockSize->h) {
						destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
		}
	}
}

BijelaKula::BijelaKula(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	bijeli = true;
	chessPieces::positions[row][column] = 2;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void BijelaKula::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
						a = 1, b = 1, c = 1, d = 1;
						hpl = false;
						hmin = false;
						vpl = false;
						vmin = false;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.w = boardBlockSize->w;
			Objects::replacementBlockDr.h = boardBlockSize->h;
			Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
			Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
			while (!hpl) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 2 || a + thisChesPos.x > 7)
					hpl = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 1) {
					a++;
					hpl = true;
				}
				else
					a++;
			}
			while (!hmin) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 2 || thisChesPos.x - b < 0)
					hmin = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 1) {
					b++;
					hmin = true;
				}
				else
					b++;
			}
			while (!vpl) {
				if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 2 || c + thisChesPos.y > 7)
					vpl = true;
				else if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 1) {
					c++;
					vpl = true;
				}
				else
					c++;
			}
			while (!vmin) {
				if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 2 || thisChesPos.y - d < 0)
					vmin = true;
				else if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 1) {
					d++;
					vmin = true;
				}
				else
					d++;
			}
			for (int i = 0; i < a; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 1) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				if (i + thisChesPos.x < 8 && chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 0) {
					Objects::replacementBlockDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < b; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - i] == 1) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < c; i++) {
				if (chessPieces::positions[thisChesPos.y + i][thisChesPos.x] == 1) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < d; i++) {
				if (chessPieces::positions[thisChesPos.y - i][thisChesPos.x] == 1) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			int measureX = (*Objects::windowWidth - 200) / 8;
			int measureY = *Objects::windowHeight / 8;
			int showingPlaceX = Events::Return_XMousePos() / measureX;
			int showingPlaceY = Events::Return_YMousePos() / measureY;
			if (showingPlaceX < a + thisChesPos.x && showingPlaceX > thisChesPos.x - b && showingPlaceX < 8 && showingPlaceY == thisChesPos.y)
				destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
			if (showingPlaceY < c + thisChesPos.y && showingPlaceY > thisChesPos.y - d && showingPlaceX == thisChesPos.x)
				destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
		}
	}
}

BijeliLovac::BijeliLovac(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	bijeli = true;
	chessPieces::positions[row][column] = 2;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void BijeliLovac::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
						RD = 1, RU = 1, LD = 1, LU = 1;
						RightDown = false;
						RightUp = false;
						LeftDown = false;
						LeftUp = false;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (chessPieces::movingState) {
		if (holding) {
			int x = thisChesPos.x;
			int y = thisChesPos.y;
			Objects::replacementBlockDr.x = x * boardBlockSize->w;
			Objects::replacementBlockDr.y = y * boardBlockSize->h;
			Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
			for (int i = y + 1; i < 8; i++) {
				for (int j = x + 1; j < 8; j++) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							RD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = 8;
						}
						else {
							i = 8;
							j = 8;
						}
					}
				}
			}
			for (int i = y + 1; i < 8; i++) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == abs(j - x)) {
						if (chessPieces::positions[i][j] == 0) {
							LD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							LD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = -1;
						}
						else {
							i = 8;
							j = -1;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x + 1; j < 8; j++) {
					if (abs(i - y) == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							RU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = 8;
						}
						else {
							i = -1;
							j = 8;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							LU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							LU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = -1;
						}
						else {
							i = -1;
							j = -1;
						}
					}
				}
			}
			int measureX = (*Objects::windowWidth - 200) / 8;
			int measureY = *Objects::windowHeight / 8;
			int showingPlaceX = Events::Return_XMousePos() / measureX;
			int showingPlaceY = Events::Return_YMousePos() / measureY;
			if ((showingPlaceX < RD + x && showingPlaceX >= x) && (showingPlaceY < RD + y && showingPlaceY >= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX < RU + x && showingPlaceX >= x) && (showingPlaceY <= y && showingPlaceY > y - RU)) {
				if (showingPlaceX - x == abs(showingPlaceY - y) && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LD && showingPlaceX <= x) && (showingPlaceY < LD + y && showingPlaceY >= y)) {
				if (abs(showingPlaceX - x) == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LU && showingPlaceX <= x) && (showingPlaceY > y - LU && showingPlaceY <= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			RD = 1;
			RU = 1;
			LD = 1;
			LU = 1;
		}
	}
}

BijelaKraljica::BijelaKraljica(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	bijeli = true;
	chessPieces::positions[row][column] = 2;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void BijelaKraljica::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
						a = 1, b = 1, c = 1, d = 1;
						hpl = false;
						hmin = false;
						vpl = false;
						vmin = false;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (chessPieces::movingState) {
		if (holding) {
			int x = thisChesPos.x;
			int y = thisChesPos.y;
			Objects::replacementBlockDr.w = boardBlockSize->w;
			Objects::replacementBlockDr.h = boardBlockSize->h;
			while (!hpl) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 2 || a + thisChesPos.x > 7)
					hpl = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x + a] == 1) {
					a++;
					hpl = true;
				}
				else
					a++;
			}
			while (!hmin) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 2 || thisChesPos.x - b < 0)
					hmin = true;
				else if (chessPieces::positions[thisChesPos.y][thisChesPos.x - b] == 1) {
					b++;
					hmin = true;
				}
				else
					b++;
			}
			while (!vpl) {
				if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 2 || c + thisChesPos.y > 7)
					vpl = true;
				else if (chessPieces::positions[thisChesPos.y + c][thisChesPos.x] == 1) {
					c++;
					vpl = true;
				}
				else
					c++;
			}
			while (!vmin) {
				if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 2 || thisChesPos.y - d < 0)
					vmin = true;
				else if (chessPieces::positions[thisChesPos.y - d][thisChesPos.x] == 1) {
					d++;
					vmin = true;
				}
				else
					d++;
			}
			for (int i = 0; i < a; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 1) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				if (i + thisChesPos.x < 8 && chessPieces::positions[thisChesPos.y][thisChesPos.x + i] == 0) {
					Objects::replacementBlockDr.x = (thisChesPos.x + i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < b; i++) {
				if (chessPieces::positions[thisChesPos.y][thisChesPos.x - i] == 1) {
					Objects::redBlockInstanceDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = (thisChesPos.x - i) * boardBlockSize->w;
					Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < c; i++) {
				if (chessPieces::positions[thisChesPos.y + i][thisChesPos.x] == 1) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y + i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = 0; i < d; i++) {
				if (chessPieces::positions[thisChesPos.y - i][thisChesPos.x] == 1) {
					Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::redBlockInstanceDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				}
				else {
					Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
					Objects::replacementBlockDr.y = (thisChesPos.y - i) * boardBlockSize->h;
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				}
			}
			for (int i = y + 1; i < 8; i++) {
				for (int j = x + 1; j < 8; j++) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							RD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = 8;
						}
						else {
							i = 8;
							j = 8;
						}
					}
				}
			}
			for (int i = y + 1; i < 8; i++) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == abs(j - x)) {
						if (chessPieces::positions[i][j] == 0) {
							LD++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							LD++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = 8;
							j = -1;
						}
						else {
							i = 8;
							j = -1;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x + 1; j < 8; j++) {
					if (abs(i - y) == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							RU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							RU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = 8;
						}
						else {
							i = -1;
							j = 8;
						}
					}
				}
			}
			for (int i = y - 1; i > -1; i--) {
				for (int j = x - 1; j > -1; j--) {
					if (i - y == j - x) {
						if (chessPieces::positions[i][j] == 0) {
							LU++;
							Objects::replacementBlockDr.x = j * boardBlockSize->w;
							Objects::replacementBlockDr.y = i * boardBlockSize->h;
							Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
						}
						else if (chessPieces::positions[i][j] == 1) {
							LU++;
							Objects::redBlockInstanceDr.x = j * boardBlockSize->w;
							Objects::redBlockInstanceDr.y = i * boardBlockSize->h;
							Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
							i = -1;
							j = -1;
						}
						else {
							i = -1;
							j = -1;
						}
					}
				}
			}
			int measureX = (*Objects::windowWidth - 200) / 8;
			int measureY = *Objects::windowHeight / 8;
			int showingPlaceX = Events::Return_XMousePos() / measureX;
			int showingPlaceY = Events::Return_YMousePos() / measureY;
			if (showingPlaceX < a + thisChesPos.x && showingPlaceX > thisChesPos.x - b && showingPlaceX < 8 && showingPlaceY == thisChesPos.y)
				destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
			if (showingPlaceY < c + thisChesPos.y && showingPlaceY > thisChesPos.y - d && showingPlaceX == thisChesPos.x)
				destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
			if ((showingPlaceX < RD + x && showingPlaceX >= x) && (showingPlaceY < RD + y && showingPlaceY >= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX < RU + x && showingPlaceX >= x) && (showingPlaceY <= y && showingPlaceY > y - RU)) {
				if (showingPlaceX - x == abs(showingPlaceY - y) && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LD && showingPlaceX <= x) && (showingPlaceY < LD + y && showingPlaceY >= y)) {
				if (abs(showingPlaceX - x) == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			if ((showingPlaceX > x - LU && showingPlaceX <= x) && (showingPlaceY > y - LU && showingPlaceY <= y)) {
				if (showingPlaceX - x == showingPlaceY - y && showingPlaceX < 8 && showingPlaceY < 8) {
					destRect->x = (boardBlockSize->w / 2) - 32 + showingPlaceX * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + showingPlaceY * boardBlockSize->h;
				}
			}
			RD = 1;
			RU = 1;
			LD = 1;
			LU = 1;
		}
	}
}

BijeliKralj::BijeliKralj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	bijeli = true;
	chessPieces::positions[row][column] = 2;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void BijeliKralj::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
			Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
			Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
			if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
				destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
				destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x + 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y][thisChesPos.x - 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = thisChesPos.y * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x] == 0) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x] == 1) {
				Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x] == 0) {
				Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x] == 1) {
				Objects::redBlockInstanceDr.x = thisChesPos.x * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
					destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
				}
			}
		}
	}
}

BijeliKonj::BijeliKonj(int row, int column, SDL_Rect* sr, SDL_Rect* dr, const char* path)
{
	bijeli = true;
	chessPieces::positions[row][column] = 2;
	loadAssets(sr, dr, path);
	setChessPosition(column, row);
}

void BijeliKonj::action()
{
	
	if (Events::Return_XMousePos() > destRect->x && Events::Return_XMousePos() < destRect->x + destRect->w) {
		if (Events::Return_YMousePos() > destRect->y && Events::Return_YMousePos() < destRect->y + destRect->h) {
			srcRect->x = 0;
			srcRect->y = 64;
			if (chessPieces::movingState) {
				if (Events::LmbPressed) {
					holdingCounter++;
					if (holdingCounter == 1) {
						holding = true;
					}
					else if (holdingCounter == 2) {
						calculateChesPieceLocation();
						holdingCounter = 0;
						holding = false;
						setExistance();
						chessPieces::setState();
						for (int i = 0; i < 8; i++) {
							for (size_t j = 0; j < 8; j++)
							{
								std::cout << chessPieces::positions[i][j] << " ";
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			srcRect->x = srcRect->y = 0;
		}
	}
	else {
		srcRect->x = srcRect->y = 0;
	}
	if (chessPieces::movingState) {
		if (holding) {
			Objects::replacementBlockDr.x = thisChesPos.x * boardBlockSize->w;
			Objects::replacementBlockDr.y = thisChesPos.y * boardBlockSize->h;
			Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
			if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
				destRect->x = (boardBlockSize->w / 2) - 32 + thisChesPos.x * boardBlockSize->w;
				destRect->y = (boardBlockSize->h / 2) - 32 + thisChesPos.y * boardBlockSize->h;
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x - 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 2][thisChesPos.x + 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x + 2] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x + 2] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x + 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x + 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x + 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x + 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x - 1] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 2][thisChesPos.x - 1] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 1) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 2) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 1) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 2) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y + 1][thisChesPos.x - 2] == 1) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y + 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y + 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 2] == 0) {
				Objects::replacementBlockDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::replacementBlockDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (replacementBlockDr.x / boardBlockSize->w < 8 && replacementBlockDr.y / boardBlockSize->h < 8)
					Objects::theReplacementBlockInstance.DrawTheObject(&Objects::replacementBlockDr, &Objects::replacementBlockSr);
				if (Events::Return_XMousePos() > replacementBlockDr.x && Events::Return_XMousePos() < replacementBlockDr.x + boardBlockSize->w && Events::Return_YMousePos() > replacementBlockDr.y && Events::Return_YMousePos() < replacementBlockDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
			if (chessPieces::positions[thisChesPos.y - 1][thisChesPos.x - 2] == 2) {
				Objects::redBlockInstanceDr.x = (thisChesPos.x - 2) * boardBlockSize->w;
				Objects::redBlockInstanceDr.y = (thisChesPos.y - 1) * boardBlockSize->h;
				if (redBlockInstanceDr.x / boardBlockSize->w < 8 && redBlockInstanceDr.y / boardBlockSize->h < 8)
					Objects::redEatingBlockInstance.DrawTheObject(&Objects::redBlockInstanceDr, &Objects::redBlockInstanceSr);
				if (Events::Return_XMousePos() > redBlockInstanceDr.x && Events::Return_XMousePos() < redBlockInstanceDr.x + boardBlockSize->w && Events::Return_YMousePos() > redBlockInstanceDr.y && Events::Return_YMousePos() < redBlockInstanceDr.y + boardBlockSize->h) {
					if (Events::Return_XMousePos() / boardBlockSize->w < 8 && Events::Return_YMousePos() / boardBlockSize->h < 8) {
						destRect->x = (boardBlockSize->w / 2) - 32 + (thisChesPos.x - 2) * boardBlockSize->w;
						destRect->y = (boardBlockSize->h / 2) - 32 + (thisChesPos.y - 1) * boardBlockSize->h;
					}
				}
			}
		}
	}
}







