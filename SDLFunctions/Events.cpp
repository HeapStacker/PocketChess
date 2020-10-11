#include "Events.h"
#include <assert.h>

SDL_Event* Events::event = nullptr;
SDL_Rect* Events::myMouse = nullptr;
bool* Events::running_mode = nullptr;
bool* Events::mainmenu_mode = nullptr;
bool* Events::options_mode = nullptr;
bool* Events::start_mode = nullptr;
bool* Events::versus_mode = nullptr;

bool Events::LmbPressed = false;
bool Events::APressed = false;
bool Events::SPressed = false;
bool Events::DPressed = false;
bool Events::WPressed = false;
bool Events::LeftPressed = false;
bool Events::DownPressed = false;
bool Events::RightPressed = false;
bool Events::UpPressed = false;
bool Events::EnterPressed = false;
bool Events::EscPressed = false;
bool Events::F11Pressed = false;
bool Events::OnePressed = false;
bool Events::TwoPressed = false;
bool Events::ThreePressed = false;
bool Events::FourPressed = false;
bool Events::FivePressed = false;
bool Events::SixPressed = false;
bool Events::SevenPressed = false;
bool Events::EightPressed = false;
bool Events::NinePressed = false;

void Events::resetKeys()
{
	Events::LmbPressed = false;
	Events::APressed = false;
	Events::SPressed = false;
	Events::DPressed = false;
	Events::WPressed = false;
	Events::LeftPressed = false;
	Events::DownPressed = false;
	Events::RightPressed = false;
	Events::UpPressed = false;
	Events::EnterPressed = false;
	Events::EscPressed = false;
	Events::F11Pressed = false;
	Events::OnePressed = false;
	Events::TwoPressed = false;
	Events::ThreePressed = false;
	Events::FourPressed = false;
	Events::FivePressed = false;
	Events::SixPressed = false;
	Events::SevenPressed = false;
	Events::EightPressed = false;
	Events::NinePressed = false;
}

void Events::EventChecker()
{
	if (SDL_PollEvent(Events::event)) {
		switch (Events::event->type) {
		case SDL_QUIT:
			//swtch = false;
			*Events::running_mode = false;
			break;
		case SDL_KEYDOWN:
			switch (Events::event->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Events::EscPressed = true;
				//swtch = false;
				break;
			case SDLK_a:
				//walkRight = true;
				Events::APressed = true;
				break;
			case SDLK_s:
				//walkRight = true;
				Events::SPressed = true;
				break;
			case SDLK_d:
				//walkRight = true;
				Events::DPressed = true;
				break;
			case SDLK_w:
				//walkRight = true;
				Events::WPressed = true;
				break;
			default:
				break;
			}
		case SDL_MOUSEMOTION:
			//std::cout << event.motion.x << "\t" << event.motion.y << std::endl;
			//ms.x = event.motion.x - mouseSize / 2;
			//ms.y = event.motion.y - mouseSize / 2;
			Events::myMouse->x = Events::event->motion.x;
			Events::myMouse->y = Events::event->motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (Events::event->button.button) {
			case SDL_BUTTON_LEFT:
				//std::cout << "Left M-button down" << std::endl;
				Events::LmbPressed = true;
				break;
			case SDL_BUTTON_RIGHT:
				//std::cout << "Right M-button down" << std::endl;
				break;
			}
		case SDL_MOUSEBUTTONUP:
			switch (Events::event->button.button) {
			case SDL_BUTTON_LEFT:
				//std::cout << "Left M-button up" << std::endl;
				break;
			case SDL_BUTTON_RIGHT:
				//std::cout << "Right M-button up" << std::endl;
				break;
			}
		default:
			break;
		}
	}
}
