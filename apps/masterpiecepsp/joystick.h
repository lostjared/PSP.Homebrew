#ifndef __JOYSTICK__H_
#define __JOYSTICK__H_


#include<SDL.h>


class Joystick {
public:
	Joystick(int num) {
		num_joy = SDL_NumJoysticks();
		OpenJoy(num);

	}
	~Joystick() {
		SDL_JoystickClose(joy);
	}

	void OpenJoy(int num) {
		joy = SDL_JoystickOpen(num);
		buttons = SDL_JoystickNumButtons(joy);
		SDL_JoystickEventState(SDL_ENABLE);
	}

	bool PollButton(int button) {

		if(SDL_JoystickGetButton(joy,button)) 
			return true;
		return false;

	}

	bool PollHat(int direction) {
		if(SDL_JoystickGetHat(joy,direction))
			return true;
		return false;
	}

	void Poll(SDL_Event &e) {
		if(e.type == SDL_JOYAXISMOTION) {
			if(e.jaxis.axis < 2)
			{
				axis[e.jaxis.axis] = e.jaxis.value >> 8;
			}
		}
	}

	SDL_Joystick *Get() { return joy; }

protected:
	int num_joy;
	SDL_Joystick *joy;
	int buttons;
public:
	int axis[2];

};

#endif