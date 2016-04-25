#include "thehead.h"

SDL_Joystick *joy;

SDL_Joystick *init_joy(int num) {
	SDL_Joystick *joy = SDL_JoystickOpen(num);
	SDL_JoystickEventState(SDL_ENABLE);
	return joy;
}
