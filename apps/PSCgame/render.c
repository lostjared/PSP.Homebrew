#include "thehead.h"
#include<stdarg.h>

SDL_Surface *cd = 0,*coin = 0,*psc = 0,*cannon = 0, *shot = 0,*logo = 0;
struct SDL_Font *fnt = 0;
int move_dir = 0, the_fire = 0, screen = 0;


void load() {

	srand((unsigned int)time(0));
	cd = SDL_LoadBMP("cd.bmp");
	psc = SDL_LoadBMP("psc.bmp");
	coin = SDL_LoadBMP("coin.bmp");
	cannon = SDL_LoadBMP("cannon.bmp");
	the_can.x = 640/2-cannon->w/2;
	the_can.y = 480-cannon->h;
	shot = SDL_LoadBMP("shot.bmp");
	logo = SDL_LoadBMP("logo.bmp");
	fnt = SDL_InitFont("arial.mxf");
}

void unload() {

	if(cd)
		SDL_FreeSurface(cd);

	if(coin)
		SDL_FreeSurface(coin);

	if(psc)
		SDL_FreeSurface(psc);

	if(cannon)
		SDL_FreeSurface(cannon);

	if(shot) 
		SDL_FreeSurface(shot);

	if(logo)
		SDL_FreeSurface(logo);

	SDL_FreeFont(fnt);

}


void printtextf(struct SDL_Font *fnt, int x, int y, SDL_Color col, const char *src, ...) {

	char buffer[2500];
	va_list l;
	va_start(l,src);
	vsprintf(buffer,src,l);
	va_end(l);

	if(fnt != 0)
	SDL_PrintTextScaled(front, fnt, x,y,15,25, SDL_MapRGB(front->format, col.r, col.g, col.b), buffer); 
}

int cd_count = 0;

void proc_game() {
	static int counter = 0;

	if(++counter > 1000) {
		if(++cd_count < 10)
		add_item_to_buffer(buff, 1);
		counter = 0;
	}
}

void proccess_logic() {
	static int counter = 0;
	proc_game();
	
	switch(move_dir) {
		case 1:
			if((the_can.x -=10) < 0)
				the_can.x = 0;
			break;
		case 2:
			if((the_can.x += 10)  > 640-cannon->w)
				the_can.x = 640-cannon->w;
			break;
	}

	if(++counter > 5) {
		if(the_fire == 1)
			rls_cash(buff);
		counter = 0;
	}
}


void render() {

	SDL_FillRect(front, 0, 0);


	switch(screen) {
		case 0:
			{
				SDL_Rect rc = { 0,0,psc->w, psc->h };
				SDL_Rect rc2 = { the_can.x, the_can.y, the_can.x+cannon->w, the_can.y+cannon->h };

				SDL_Color col = { rand()%255, rand()%255, rand()%255 };

				proccess_logic();
				SDL_BlitSurface(psc, 0, front, &rc );
				printtextf(fnt, psc->w,20, col, " Score: %d Miss: %d", score, miss);
			
				SDL_SetColorKey(cannon, SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255, 0, 255) );
				SDL_BlitSurface(cannon, 0, front, &rc2 );
				proccess_nodes(buff);
			}
			break;
		case 1:
			{
				SDL_Color c1 = { rand()%255, rand()%255, rand()%255 };
				SDL_Color c2 = { 255, 0, 0 };
				SDL_BlitSurface(logo, 0, front, 0);
				printtextf(fnt, 100,100, c1 , "GAME OVER SCORE: %d", score);
				printtextf(fnt, 100,200, c2 , "Press any key to play agian");
			}
			break;
	}
	
	SDL_UpdateRect(front, 0,0,640,480);
}

