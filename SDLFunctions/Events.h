#pragma once
#include <vector>
#include "SDL.h"

class Events
{
public:
	static int Return_XMousePos() {
		return Events::myMouse->x + (Events::myMouse->w / 2);  //For pointing functions
	}
	static int Return_YMousePos() {
		return Events::myMouse->y + (Events::myMouse->h / 2);  //For pointing functions
	}
	static SDL_Rect* myMouse;
	static SDL_Event* event;
	static void resetKeys();
	static void EventChecker();
	static bool *running_mode, *mainmenu_mode, *options_mode, *start_mode, *versus_mode;
	static bool LmbPressed, APressed, SPressed, DPressed, WPressed, LeftPressed, DownPressed, RightPressed, UpPressed;
	static bool EnterPressed, EscPressed, F11Pressed, OnePressed, TwoPressed, ThreePressed, FourPressed, FivePressed;
	static bool SixPressed, SevenPressed, EightPressed, NinePressed;
};
