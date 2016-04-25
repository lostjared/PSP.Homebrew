

#include"froggy.h"
#include <pspkerneltypes.h>	//# |_ For 333Mhz Overclock
#include <psppower.h>		//# |

SDL_Surface *front;
SDL_Surface *intro;
SDL_Surface *credit;
SDL_Joystick *stick;
int scr = 0;

typedef struct _Credit {

	int x,y,index,off;

} Credit;

static char *str_array[] = { "Road Kill 1.0", "Written by", "Jared && Shannon Bruni", "In 2 days", "Graphics by", "Shannon Bruni", "Code By", "Jared Bruni", "(C) 2006 LostSideDead", "Have fun", "cause we did!", "This game", "Is dedicated", "To my", "best friend/fiance'", "Shannon", "I Love you", 0 };

Credit cr[17];

/*

 0 Triangle
 1 Circle
 2 Cross
 3 Square
 4 Left trigger
 5 Right trigger
 6 Down
 7 Left
 8 Up
 9 Right
10 Select
11 Start
12 Home
13 Hold

*/

void render_intro() {

	Uint8 *key = SDL_GetKeyState(0);
	
	SDL_BlitSurface(intro, 0, front, 0);
	SDL_PrintText(front, font, 480/2-120, 272-20, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "Press Start to Play");
	
	if(key[SDLK_SPACE]) {
		scr = 1;
		new_game();
	}

	if(SDL_JoystickGetButton(stick, 11)) {
		scr = 1;
		new_game();
	}

}

void init_credits() {
	
	int i;
	memset(cr, 0, sizeof(cr));
	for(i = 0; i < 17; i++) {

		cr[i].x = 250;
		cr[i].y = 250;
		cr[i].index = i;
		cr[i].off = 0;
	}

	cr[0].off = 1;
}

void render_credits() {


	int i;
	static int index = 0;
	static int c = 0;
	SDL_BlitSurface(credit, 0, front, 0);

	// rasterize the text
	for(i = 0; i < 17; i++) {

		if(cr[i].off == 1) {

			SDL_PrintText(front, font, cr[i].x, cr[i].y, SDL_MapRGB(front->format, 0, 255, 0), str_array[cr[i].index]);
			SDL_Delay(10);
			cr[i].y--;
		
		}
	
	}
	

	if((++c % 25) == 0) {

		cr[index].off = 1;
		index++;
		

	}

	
	if(cr[index].y <= 0)
		cr[index].off = 0;
	if(cr[16].y <= 0)
	{
		scr = 0;
		init_credits();
	}
	
}

int main(int argc, char **argv) {

	static SDL_Event e;
	int active = 1;
	
	

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
	return -1;
	
	front = SDL_SetVideoMode(480,272,0,0); //SDL_FULLSCREEN);
	if(!front) {
		fprintf(stderr, "Error setting video mode\n");
		return -1;
	}
	
	scePowerSetClockFrequency(333, 333, 166); //# overclocked

	stick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);


	intro = SDL_LoadBMP("img/intro.bmp");
	credit = SDL_LoadBMP("img/credits.bmp");
	init_credits();
	init();

	SDL_WM_SetCaption("RoadKill - by Jared && Shannon Bruni", 0);
	scr = 0;
	
	while(active == 1) {

		SDL_FillRect(front, 0, 0);
		switch(scr) {
		case 0:
		render_intro();
		break;
		case 1:
		render();
		break;
		case 2:
		render_credits();
		break;
		}

		if(SDL_PollEvent(&e)) {

			switch(e.type) {
			case SDL_QUIT:
			active = 0;
			break;
			case SDL_KEYDOWN:
			if(e.key.keysym.sym == SDLK_ESCAPE)
				active = 0;
			break;
			}
		}

		SDL_Flip(front);
	}

	free_gfx();
	SDL_FreeSurface(front);
	SDL_FreeSurface(intro);
	SDL_FreeSurface(credit);
	SDL_JoystickClose(stick);
	SDL_Quit();
	return 0;
}


