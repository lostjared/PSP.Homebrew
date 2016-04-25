#include "puzzle.h"

#include <SDL.h>


screen_type scr = ID_INTRO;


void *lock(SDL_Surface *surf, Uint8 &type) {
	if(SDL_MUSTLOCK(surf)) {
		if(SDL_LockSurface(surf) < 0)
			return 0;
	}

	type = surf->format->BitsPerPixel;

	switch(surf->format->BitsPerPixel) {
		case 1:
		case 8:
			return (Uint8*)surf->pixels;
			break;
		case 16:
		case 2:
			return (Uint16*)surf->pixels;
			break;
		case 24:
		case 3:
			return (Uint32*)surf->pixels;
			break;
		case 32:
		case 4:
			return (Uint32*)surf->pixels;
			break;
		default:
			break;
	}

	return 0;

}



void unlock(SDL_Surface *surf) {
	if(SDL_MUSTLOCK(surf)) {
		SDL_UnlockSurface(surf);
	}
}



inline void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 &type, Uint16 &pitch) {
	static Uint8 *ubuff8 = 0;

	switch(type) {
		case 1:
		case 8:
			{ 
				Uint8 *buf = (Uint8*)buff;
				buf += (y * pitch) + x;
				*buf = (Uint8) color;

			}
			break;
		case 2:
		case 16:
			{
				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*2);
				static Uint16 *ubuff16 = 0;
				ubuff16 = (Uint16*) ubuff8;
				*ubuff16 = (Uint16) color;
			}
			break;
		case 3:
		case 24:
			{
				static char c1 = 0,c2 = 0,c3 = 0;

				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*3);
				if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
					c1 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c3 = (color & 0x0000FF);
				} else {
					c3 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c1 = (color & 0x0000FF);
				}
				ubuff8[0] = c3;
				ubuff8[1] = c2;
				ubuff8[2] = c1;
			}
			break;
		case 4:
		case 32:
			{
			ubuff8 = (Uint8*) buff;
			static Uint32 *ubuff32 = 0;
			ubuff8 += (y*pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			}
			break;
	}

}

inline Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 &type, Uint16 &pitch) {
	static Uint8 *bitz = 0;
	Uint32 bpp = (Uint32) type;
	bitz = ((Uint8 *)surf->pixels)+y*pitch+x*(bpp/8);
	switch(type) {
		case 8:
		case 1:
			return *((Uint8 *)surf->pixels + y * pitch + x);
			break;
		case 16:
		case 2:
			return *((Uint16 *)surf->pixels + y * pitch/2 + x);
			break;
		case 3:
		case 24:
			{
				Uint8 r, g, b;
				r = *((bitz)+surf->format->Rshift/8);
				g = *((bitz)+surf->format->Gshift/8);
				b = *((bitz)+surf->format->Bshift/8);
				return SDL_MapRGB(surf->format,r,g,b);
			
			}
		case 32:
		case 4:
			return *((Uint32 *)surf->pixels + y * pitch/4 + x);
			break;
	}

	return 0;
}

extern "C" int SDL_main(int argc, char **argv);

int SDL_main(int argc, char **argv) {

	SDL_Surface *front = 0;

	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;
	atexit(SDL_Quit);
	front = SDL_SetVideoMode(480,272,0,0);

	if(!front)
		return -2;

	Joystick j(0);

	SDL_Event e;
	bool active = true;
	
	char *argument = "intro.bmp";

	PuzzleBox box(front,argument,50);

	SDL_Surface *logo =SDL_LoadBMP("logo.bmp");

	while(active == true) {

		//SDL_Rect rc = { 0,0,480,272 };
		static Uint8 type = 0;
		switch(scr) {
		case ID_GAME:
			{
		void *raw = lock(front,type);
		box.render(raw,type,front->pitch);
		unlock(front);
			}
		break;
		case ID_INTRO: 
			{
			SDL_Rect rc = { 0,0,480,272 };
			SDL_FillRect(front, &rc, 0x0 );
			SDL_BlitSurface(logo, &rc, front, &rc );
			SDL_Color col = { 255,0 ,0 };
			box.printtextf(50,50,col,"Press Start to Begin ");

			}
			break;
		case ID_GAMEOVER:
			SDL_Rect rc = { 0,0,480,272 };
			SDL_FillRect(front, &rc, SDL_MapRGB(front->format, rand()%255,rand()%255,rand()%255) );
			
			SDL_Color col = {rand()%255,0,0};
			box.printtextf(50,50,col,"Game Over Score %d start to quit", box.score);
			break;
		}

		if(j.PollButton(11)) {
			if(scr == ID_GAMEOVER)
				box.init_blocks();
			setscreen(ID_GAME);
		}

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = false;
					break;
				case SDL_JOYBUTTONDOWN:

					switch(e.jbutton.button) 
					{
					//case SDL_HAT_CENTERED:
					//	break;
					case 8:
						box.switch_color(box.blocks);
						box.move_up();
						box.setcdir(0);
						break;
					case 9:
						box.move_right();
						box.setcdir(1);
						break;
					case 6:
						box.setcdir(2);
						box.move_down();
						break;
					case 7:
						box.move_left();
						box.setcdir(3);
						break;
					}

					switch(e.jbutton.button)
					{
					case 0:
						box.switch_color(box.blocks);
						break;
					case 1:
						{
							box.merge_blocks();
						}
						break;
					}
					break;
			}
		}

		SDL_UpdateRect(front, 0, 0, 480,272);
	}

	SDL_FreeSurface(logo);
	SDL_FreeSurface(front);
	return 0;
}

void setscreen(screen_type t) {
	scr = t;
}
