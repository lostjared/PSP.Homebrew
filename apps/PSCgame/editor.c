//  LostSideDead
#include"thehead.h"

SDL_Surface *front = 0;
struct array_buffer *buff = 0;
struct cannon the_can;

extern int SDL_main(int argc, char **argv);


int SDL_main(int argc, char **argv) {


	SDL_Event e;
	int active = 1;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		fprintf(stderr, "Error couldnt initalize SDL\n");
		return 0;
	}

	atexit(SDL_Quit);

	front = SDL_SetVideoMode(640,480,0,0);
	if(!front) {
		fprintf(stderr, "Error couldnt set video mode\n");
		return 0;
	}
	SDL_WM_SetCaption("E-Ninja", 0);
	joy = init_joy(0);
	load();
	buff = add_item_to_buffer(0, 1);

	add_item_to_buffer(buff, 2);

	while(active == 1) {

		
		render();
		SDL_UpdateRect(front, 0,0,640,480);
		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
				case SDL_JOYBUTTONDOWN:
					{
						if(screen == 0)
						switch(e.jbutton.button)
						{
						case 0:
						case 1:
						case 2:
						case 3:
							the_fire = 1;
							break;
						case 7:
							move_dir = 1;
							break;
						case 9:
							move_dir = 2;
							break;
						}
						else
							new_game();
					}
					break;
				case SDL_JOYBUTTONUP:
					{
						switch(e.jbutton.button) 
						{
						case 0:
						case 1:
						case 2:
						case 3:
							the_fire = 0;
							break;
						case 7:
						case 9:
							move_dir = 0;
							break;
						}
					}
					break;
/*
				case SDL_KEYDOWN:
					{
						if(screen == 0) {
							switch(e.key.keysym.sym) 
							{
							case SDLK_LEFT:
								move_dir = 1;
								break;
							case SDLK_RIGHT:
								move_dir = 2;
								break;
							case SDLK_SPACE:
								the_fire = 1;
								break;
							}
						}
						else new_game();
					}
					break;
				case SDL_KEYUP:
					{
						switch(e.key.keysym.sym) 
						{
						case SDLK_LEFT:
						case SDLK_RIGHT:
							move_dir = 0;
							break;
						case SDLK_SPACE:
							the_fire = 0;
							break;
						}
					}
					break;
*/// rm'd for porting purposes

			}
		}
	}

	free_nodes(buff);
	unload();
	SDL_FreeSurface(front);
	SDL_JoystickClose(joy);
	return 0;
}