#include <thread>
#include <chrono>
#include <memory>
#include <vector>
#include "Inits.h"
#include "ImageLoader.h"
#include "Events.h"
#include "SoundSystem.h"
#include "Pieces.h"

//Some inits...
int frameCount = 0;
int ww = 0, wh = 0;

//Object initialisation...
Events ev = Events();
ImageLoader backgroundImage = ImageLoader();
ImageLoader Mouse = ImageLoader();
Objects* backButton_ptr;


//Main-menu obs
std::vector<std::unique_ptr<Objects>> MainMenuObjects;
Objects* startButton_ptr;
Objects* optionsButton_ptr;
Objects* quitButton_ptr;


//Mods-menu obs
std::vector<std::unique_ptr<Objects>> ModSelectorObjects;
Objects* singlePlayerButton_ptr;
Objects* versusButton_ptr;
Objects* multyPlayerButton_ptr;


//Versus mode obs
ImageLoader blackBoard = ImageLoader();
ImageLoader whiteBoard = ImageLoader();
ImageLoader replacementBoard = ImageLoader();
std::vector<std::unique_ptr<chessPieces>> VersusModeObjects;
chessPieces* crniPijun1_ptr;
chessPieces* crniPijun2_ptr;
chessPieces* crniPijun3_ptr;
chessPieces* crniPijun4_ptr;
chessPieces* crniPijun5_ptr;
chessPieces* crniPijun6_ptr;
chessPieces* crniPijun7_ptr;
chessPieces* crniPijun8_ptr;
chessPieces* crnaKulaL_ptr;
chessPieces* crnaKulaR_ptr;
chessPieces* crniLovacL_ptr;
chessPieces* crniLovacR_ptr;
chessPieces* crnaKraljica_ptr;
chessPieces* crniKralj_ptr;
chessPieces* crniKonjR_ptr;
chessPieces* crniKonjL_ptr;
chessPieces* bijeliPijun1_ptr;
chessPieces* bijeliPijun2_ptr;
chessPieces* bijeliPijun3_ptr;
chessPieces* bijeliPijun4_ptr;
chessPieces* bijeliPijun5_ptr;
chessPieces* bijeliPijun6_ptr;
chessPieces* bijeliPijun7_ptr;
chessPieces* bijeliPijun8_ptr;
chessPieces* bijelaKulaL_ptr;
chessPieces* bijelaKulaR_ptr;
chessPieces* bijeliLovacL_ptr;
chessPieces* bijeliLovacR_ptr;
chessPieces* bijelaKraljica_ptr;
chessPieces* bijeliKralj_ptr;
chessPieces* bijeliKonjR_ptr;
chessPieces* bijeliKonjL_ptr;
Objects* boardWithStatsInstance;


static void createVectorOfMainMenuObj(Objects* obj);
static void createVectorOfModSelectorObj(Objects* obj);
static void createVectorOfVersusModeObj(chessPieces* obj);
static void MainMenu();
static void ModSelectorMenu();
static void VersusMode();
static void deleteThoseOtherPtrs() {
	delete boardWithStatsInstance;
}
int main(int argc, char* argv[]) {
	removeCMD();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		PROBLEM_DETECTION();
	}
	if (IMG_Init(IMG_INIT_PNG) != 2 && IMG_Init(IMG_INIT_JPG) != 1) {
		SDL_Quit();
		PROBLEM_DETECTION();
	}
	window = SDL_CreateWindow("PocketChess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		IMG_Quit();
		SDL_Quit();
		PROBLEM_DETECTION();
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //brži od od SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		PROBLEM_DETECTION();
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		PROBLEM_DETECTION();
	}
	std::chrono::nanoseconds frameDuration = std::chrono::nanoseconds(1000000000) / FramesPerSecond;


	//Object initialisation...
	try
	{
		Objects::window = window;
		if (!Objects::window)
			throw 1;
		Objects::renderer = renderer;
		if (!Objects::renderer)
			throw 2;
		Events::running_mode = &running;
		if (!Events::running_mode)
			throw 3;
		Events::mainmenu_mode = &mmmod;
		if (!Events::mainmenu_mode)
			throw 4;
		Events::options_mode = &options;
		if (!Events::options_mode)
			throw 5;
		Events::start_mode = &modsell;
		if (!Events::start_mode)
			throw 6;
		Events::versus_mode = &versus;
		if (!Events::versus_mode)
			throw 7;
		Events::myMouse = &mouse;
		if (!Events::myMouse)
			throw 8;
		Events::event = &event;
		if (!Events::event)
			throw 9;
		ImageLoader::renderer = renderer;
		if (!ImageLoader::renderer)
			throw 10;
		Objects::initWindowWidth = windowWidth;
		Objects::initWindowHeight = windowHeight;
		Objects::windowWidth = &windowWidth;
		if (Objects::windowWidth == nullptr)
			throw 11;
		Objects::windowHeight = &windowHeight;
		if (Objects::windowHeight == nullptr)
			throw 12;
		ww = *Objects::windowWidth;
		wh = *Objects::windowHeight;
		Objects::boardBlockSize = &whiteBoardPieceDr;
		if (Objects::boardBlockSize == nullptr)
			throw 13;
	}
	catch (const int num)
	{
		showCMD();
		std::cerr << num << std::endl;
	}
	rect.w = 0.2 * windowWidth;
	rect.h = 0.2 * windowHeight;
	rect.x = (windowWidth / 2) - (rect.w / 2);
	rect.y = (windowHeight / 2) - (rect.h / 2);
	mouse.w = mouse.h = mouseSize;
	backgroundImage.SetTexture(&backgroundSr, "Assets/background.png");
	blackBoard.SetTexture(&blackBoardPieceSr, "Assets/BlackBoardPiece.png");
	whiteBoard.SetTexture(&whiteBoardPieceSr, "Assets/WhiteBoardPiece.png");
	Mouse.SetTexture(&mouse, "Assets/cursor.png");

	//Kreiranje replacemnt-block-a..
	/*Objects::replacementBlockTexture = replacementBoard.setReturnTexture(&replacementBlockSr, "Assets/BlackBoardPiece.png");*/
	Objects::createReplacementBlockClass();
	Objects::createRedEatingBlockInstance();

	
	//Game-Loop...
	{
		//Main-menu obs...
		startButton_ptr = new Start_Button();
		startButton_ptr->loadAssets(&startButtonSr, &startButtonDr, "Assets/play_button.png");
		createVectorOfMainMenuObj(std::move(startButton_ptr));
		optionsButton_ptr = new Options_Button();
		optionsButton_ptr->loadAssets(&optionsButtonSr, &optionsButtonDr, "Assets/options_button.png");
		createVectorOfMainMenuObj(std::move(optionsButton_ptr));
		quitButton_ptr = new Quit_Button();
		quitButton_ptr->loadAssets(&quitButtonSr, &quitButtonDr, "Assets/quit_button.png");
		createVectorOfMainMenuObj(std::move(quitButton_ptr));
		

		//Mod-selector items...
		singlePlayerButton_ptr = new SinglePlayer_Button();
		singlePlayerButton_ptr->loadAssets(&singleplayerButtonSr, &singleplayerButtonDr, "Assets/singlePlayer_button.png");
		createVectorOfModSelectorObj(std::move(singlePlayerButton_ptr));
		versusButton_ptr = new Versus_Button();
		versusButton_ptr->loadAssets(&versusButtonSr, &versusButtonDr, "Assets/versus_button.png");
		createVectorOfModSelectorObj(std::move(versusButton_ptr));
		multyPlayerButton_ptr = new MultyPlayer_Button();
		multyPlayerButton_ptr->loadAssets(&multyplayerSr, &multyplayerDr, "Assets/multyPlayer_button.png");
		createVectorOfModSelectorObj(std::move(multyPlayerButton_ptr));
		backButton_ptr = new Back_Button();
		backButton_ptr->loadAssets(&bButtonSr, &bButtonDr, "Assets/back_button.png");
		createVectorOfModSelectorObj(std::move(backButton_ptr));


		//Versus mode items...
		crniPijun1_ptr = new CrniPijun(1, 0, &blackPijunSr1, &blackPijunDr1, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun1_ptr));
		crniPijun2_ptr = new CrniPijun(1, 1, &blackPijunSr2, &blackPijunDr2, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun2_ptr));
		crniPijun3_ptr = new CrniPijun(1, 2, &blackPijunSr3, &blackPijunDr3, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun3_ptr));
		crniPijun4_ptr = new CrniPijun(1, 3, &blackPijunSr4, &blackPijunDr4, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun4_ptr));
		crniPijun5_ptr = new CrniPijun(1, 4, &blackPijunSr5, &blackPijunDr5, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun5_ptr));
		crniPijun6_ptr = new CrniPijun(1, 5, &blackPijunSr6, &blackPijunDr6, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun6_ptr));
		crniPijun7_ptr = new CrniPijun(1, 6, &blackPijunSr7, &blackPijunDr7, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun7_ptr));
		crniPijun8_ptr = new CrniPijun(1, 7, &blackPijunSr8, &blackPijunDr8, "Assets/cat.png");
		createVectorOfVersusModeObj(std::move(crniPijun8_ptr));
		crnaKulaL_ptr = new CrnaKula(0, 7, &blackCastleLSr, &blackCastleLDr, "Assets/dog.png");
		createVectorOfVersusModeObj(std::move(crnaKulaL_ptr));
		crnaKulaR_ptr = new CrnaKula(0, 0, &blackCastleRSr, &blackCastleRDr, "Assets/dog.png");
		createVectorOfVersusModeObj(std::move(crnaKulaR_ptr));
		crniLovacL_ptr = new CrniLovac(0, 2, &blackHunterLSr, &blackHunterLDr, "Assets/hunter.png");
		createVectorOfVersusModeObj(std::move(crniLovacL_ptr));
		crniLovacR_ptr = new CrniLovac(0, 5, &blackHunterRSr, &blackHunterRDr, "Assets/hunter.png");
		createVectorOfVersusModeObj(std::move(crniLovacR_ptr));
		crnaKraljica_ptr = new CrnaKraljica(0, 3, &blackQuinSr, &blackQuinDr, "Assets/quin.png");
		createVectorOfVersusModeObj(std::move(crnaKraljica_ptr));
		crniKralj_ptr = new CrniKralj(0, 4, &blackKingSr, &blackKingDr, "Assets/king.png");
		createVectorOfVersusModeObj(std::move(crniKralj_ptr));
		crniKonjR_ptr = new CrniKonj(0, 1, &blackHorseRSr, &blackHorseRDr, "Assets/horse.png");
		createVectorOfVersusModeObj(std::move(crniKonjR_ptr));
		crniKonjL_ptr = new CrniKonj(0, 6, &blackHorseLSr, &blackHorseLDr, "Assets/horse.png");
		createVectorOfVersusModeObj(std::move(crniKonjL_ptr));
		bijeliPijun1_ptr = new BijeliPijun(6, 0, &whitePijunSr1, &whitePijunDr1, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun1_ptr));
		bijeliPijun2_ptr = new BijeliPijun(6, 1, &whitePijunSr2, &whitePijunDr2, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun2_ptr));
		bijeliPijun3_ptr = new BijeliPijun(6, 2, &whitePijunSr3, &whitePijunDr3, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun3_ptr));
		bijeliPijun4_ptr = new BijeliPijun(6, 3, &whitePijunSr4, &whitePijunDr4, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun4_ptr));
		bijeliPijun5_ptr = new BijeliPijun(6, 4, &whitePijunSr5, &whitePijunDr5, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun5_ptr));
		bijeliPijun6_ptr = new BijeliPijun(6, 5, &whitePijunSr6, &whitePijunDr6, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun6_ptr));
		bijeliPijun7_ptr = new BijeliPijun(6, 6, &whitePijunSr7, &whitePijunDr7, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun7_ptr));
		bijeliPijun8_ptr = new BijeliPijun(6, 7, &whitePijunSr8, &whitePijunDr8, "Assets/white_cat.png");
		createVectorOfVersusModeObj(std::move(bijeliPijun8_ptr));
		bijelaKulaL_ptr = new BijelaKula(7, 0, &whiteCastleLSr, &whiteCastleLDr, "Assets/white_dog.png");
		createVectorOfVersusModeObj(std::move(bijelaKulaL_ptr));
		bijelaKulaR_ptr = new BijelaKula(7, 7, &whiteCastleRSr, &whiteCastleRDr, "Assets/white_dog.png");
		createVectorOfVersusModeObj(std::move(bijelaKulaR_ptr));
		bijeliLovacL_ptr = new BijeliLovac(7, 2, &whiteHunterLSr, &whiteHunterLDr, "Assets/white_hunter.png");
		createVectorOfVersusModeObj(std::move(bijeliLovacL_ptr));
		bijeliLovacR_ptr = new BijeliLovac(7, 5, &whiteHunterRSr, &whiteHunterRDr, "Assets/white_hunter.png");
		createVectorOfVersusModeObj(std::move(bijeliLovacR_ptr));
		bijelaKraljica_ptr = new BijelaKraljica(7, 3, &whiteQuinSr, &whiteQuinDr, "Assets/white_quin.png");
		createVectorOfVersusModeObj(std::move(bijelaKraljica_ptr));
		bijeliKralj_ptr = new BijeliKralj(7, 4, &whiteKingSr, &whiteKingDr, "Assets/white_king.png");
		createVectorOfVersusModeObj(std::move(bijeliKralj_ptr));
		bijeliKonjR_ptr = new BijeliKonj(7, 1, &whiteHorseRSr, &whiteHorseRDr, "Assets/white_horse.png");
		createVectorOfVersusModeObj(std::move(bijeliKonjR_ptr));
		bijeliKonjL_ptr = new BijeliKonj(7, 6, &whiteHorseLSr, &whiteHorseLDr, "Assets/white_horse.png");
		createVectorOfVersusModeObj(std::move(bijeliKonjL_ptr));
		boardWithStatsInstance = new statusBoard();
		boardWithStatsInstance->loadAssets(&boardWithStatsSr, &boardWithStatsDr, "Assets/statusBoard.png");


		SDL_ShowCursor(0);
		while (*Events::running_mode) {
			//main-menu
			while (*Events::running_mode && *Events::mainmenu_mode && !*Events::start_mode && !*Events::options_mode && !*Events::versus_mode) {
				std::chrono::high_resolution_clock::time_point firstPoint = std::chrono::high_resolution_clock::now();
				ev.EventChecker();
				MainMenu();
				ev.resetKeys();
				Objects::initWindowWidth = *Objects::windowWidth;   //After a change in a window scale all obs and after that set new window size.
				Objects::initWindowHeight = *Objects::windowHeight;
				std::chrono::high_resolution_clock::time_point lastPoint = std::chrono::high_resolution_clock::now();
				std::chrono::high_resolution_clock::duration duration = lastPoint - firstPoint;
				if (duration < frameDuration)
					std::this_thread::sleep_for(frameDuration - duration);
			}
			//mod-sellector
			while (*Events::running_mode && *Events::mainmenu_mode && *Events::start_mode && !*Events::options_mode && !*Events::versus_mode) {
				std::chrono::high_resolution_clock::time_point firstPoint = std::chrono::high_resolution_clock::now();
				ev.EventChecker();
				ModSelectorMenu();
				ev.resetKeys();
				Objects::initWindowWidth = *Objects::windowWidth;   //After a change in a window scale all obs and after that set new window size.
				Objects::initWindowHeight = *Objects::windowHeight;
				std::chrono::high_resolution_clock::time_point lastPoint = std::chrono::high_resolution_clock::now();
				std::chrono::high_resolution_clock::duration duration = lastPoint - firstPoint;
				if (duration < frameDuration)
					std::this_thread::sleep_for(frameDuration - duration);
			}
			//versus mode
			showCMD();
			while (*Events::running_mode && *Events::mainmenu_mode && *Events::start_mode && !*Events::options_mode && *Events::versus_mode) {
				std::chrono::high_resolution_clock::time_point firstPoint = std::chrono::high_resolution_clock::now();
				ev.EventChecker();
				VersusMode();
				ev.resetKeys();
				Objects::initWindowWidth = *Objects::windowWidth;   //After a change in a window scale all obs and after that set new window size.
				Objects::initWindowHeight = *Objects::windowHeight;
				std::chrono::high_resolution_clock::time_point lastPoint = std::chrono::high_resolution_clock::now();
				std::chrono::high_resolution_clock::duration duration = lastPoint - firstPoint;
				if (duration < frameDuration)
					std::this_thread::sleep_for(frameDuration - duration);
			}
		}
	}

	removeCMD();
	deleteThoseOtherPtrs();
	Mix_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}

void createVectorOfMainMenuObj(Objects* obj) {
	std::unique_ptr<Objects> uPtr(obj);
	MainMenuObjects.emplace_back(std::move(uPtr));
}

void createVectorOfModSelectorObj(Objects* obj) {
	std::unique_ptr<Objects> uPtr(obj);
	ModSelectorObjects.emplace_back(std::move(uPtr));
}

void createVectorOfVersusModeObj(chessPieces* obj) {
	std::unique_ptr<chessPieces> uPtr(obj);
	VersusModeObjects.emplace_back(std::move(uPtr));
}

void MainMenu() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	drawForX = 1 + (*Objects::windowWidth / backgroundSr.w);
	drawForY = 1 + (*Objects::windowHeight / backgroundSr.h);
	for (int i = 0; i < drawForY; i++) {
		backgroundDr.y = i * backgroundDr.h;
		for (int j = 0; j < drawForX; j++) {
			backgroundDr.x = j * backgroundDr.w;
			backgroundImage.DrawTheObject(&backgroundDr, &backgroundSr);
		}
	}
	backgroundDr.x = 0;
	backgroundDr.y = 0;
	for (auto& obj : MainMenuObjects) {
		obj->draw();
	}
	Mouse.DrawTheObject(Events::myMouse, nullptr);
	SDL_RenderPresent(renderer);
}

void ModSelectorMenu()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	drawForX = 1 + (*Objects::windowWidth / backgroundSr.w);
	drawForY = 1 + (*Objects::windowHeight / backgroundSr.h);
	for (int i = 0; i < drawForY; i++) {
		backgroundDr.y = i * backgroundDr.h;
		for (int j = 0; j < drawForX; j++) {
			backgroundDr.x = j * backgroundDr.w;
			backgroundImage.DrawTheObject(&backgroundDr, &backgroundSr);
		}
	}
	backgroundDr.x = 0;
	backgroundDr.y = 0;
	for (auto& obj : ModSelectorObjects) {
		obj->draw();
	}
	Mouse.DrawTheObject(Events::myMouse, nullptr);
	SDL_RenderPresent(renderer);
}

void VersusMode()
{
	SDL_SetRenderDrawColor(renderer, 200, 134, 35, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int scalarX = 0, scalarY = 0;
	{
		SDL_GetWindowSize(Objects::window, Objects::windowWidth, Objects::windowHeight);
		if (*Objects::windowWidth != ww)
			scalarX = (*Objects::windowWidth - ww) / 8;
		if (*Objects::windowHeight != wh)
			scalarY = (*Objects::windowHeight - wh) / 8;
		boardWithStatsInstance->draw();
		for (int a = 0; a < 8; a++) {
			whiteBoardPieceDr.y = a * scalarY + whiteBoardPieceSr.h * a;
			blackBoardPieceDr.y = a * scalarY + blackBoardPieceSr.h * a;
			for (int i = 0; i < 8; i += 2) {
				blackBoardPieceDr.w = blackBoardPieceSr.w + scalarX;
				blackBoardPieceDr.h = blackBoardPieceSr.h + scalarY;
				whiteBoardPieceDr.w = whiteBoardPieceSr.w + scalarX;
				whiteBoardPieceDr.h = whiteBoardPieceSr.h + scalarY;
				if ((a % 2 == 0) || a == 0) {
					whiteBoardPieceDr.x = whiteBoardPieceSr.w * i + i * scalarX;
					whiteBoard.DrawTheObject(&whiteBoardPieceDr, &whiteBoardPieceSr);
					blackBoardPieceDr.x = blackBoardPieceSr.w * (i + 1) + (i + 1) * scalarX;
					blackBoard.DrawTheObject(&blackBoardPieceDr, &blackBoardPieceSr);
				}
				else {
					blackBoardPieceDr.x = blackBoardPieceSr.w * i + i * scalarX;
					blackBoard.DrawTheObject(&blackBoardPieceDr, &blackBoardPieceSr);
					whiteBoardPieceDr.x = whiteBoardPieceSr.w * (i + 1) + (i + 1) * scalarX;
					whiteBoard.DrawTheObject(&whiteBoardPieceDr, &whiteBoardPieceSr);
				}
			}
		}
		for (auto& obj : VersusModeObjects) 
			obj->draw();
		VersusModeObjects.erase(std::remove_if(VersusModeObjects.begin(), VersusModeObjects.end(), [](const std::unique_ptr<chessPieces>& obj) {
			return obj->deleteMe;
			}), VersusModeObjects.end());
	}
	Mouse.DrawTheObject(Events::myMouse, nullptr);
	SDL_RenderPresent(renderer);
}

 