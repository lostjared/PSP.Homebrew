#include <pspkerneltypes.h>	//# |_ For 333Mhz Overclock
#include <psppower.h>		//# |
#include<SDL.h>
#include<SDL_mxf.h>
#include<stdlib.h>

struct SDL_Font *the_font = 0;


struct Letter {
	int x,y;
	int speed;
	char c[30];
	Uint32 color;
};

struct Letter letters[100];

char randletter(int max) {
	char c;
	do {
		c = rand()%max;
	} while( c > 33 && c < 128 );
	return c;
}

void init_letters(SDL_Surface *surf) {
	int i,z;
	for(i = 0; i < 100; i++) {
		for(z = 0; z < 30; z++)
		letters[i].c[z] = randletter(128);
		letters[i].x = i*14;
		letters[i].y = -30*12;
		do 
		letters[i].speed = rand()%10;
			while(letters[i].speed <= 0);
		letters[i].color = SDL_MapRGB(surf->format, 0, 255, 0);
	}
}


void draw(SDL_Surface *surf) {
	int i,z;
	for(i = 0; i < 100; i++)
	{
		for(z = 0; z < 30; z++) {
			char buf[2];
			buf[0] = letters[i].c[z];
			buf[1] = 0;
			if(letters[i].y+(z*12) > 0)
			SDL_PrintText(surf, the_font, letters[i].x, letters[i].y+(z*12), letters[i].color, buf);
		}

		if(letters[i].y < surf->h)
			letters[i].y += letters[i].speed;

		if(letters[i].y >= surf->h) {
			letters[i].y = -30*12;
			do
			letters[i].speed = rand()%10;
			while (letters[i].speed <= 0);
		}
	}

}

int SDL_main(int argc, char **argv) {

	scePowerSetClockFrequency(333, 333, 166); //# overclocked
//	scePowerSetClockFrequency(222, 222, 111); //# default

	SDL_Surface *front = 0;
	int active = 1;
	SDL_Event e;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	if(!(front = SDL_SetVideoMode(640,480,0,0)))
		return -1;


	the_font = SDL_InitFont("font.mxf");
	if(!the_font)
		return -1;


	init_letters(front);

	while(active == 1) {

		SDL_FillRect(front, 0, 0);

		draw(front);
		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
			}
		}

		SDL_UpdateRect(front, 0, 0, 640, 480);

	}


	SDL_FreeFont(the_font);
	SDL_FreeSurface(front);
	SDL_Quit();

	return 0;
}