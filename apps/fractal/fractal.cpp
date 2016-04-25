#include<SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include"joystick.h"


void *lock(SDL_Surface *surf, Uint8 type) {
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

void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 type, Uint16 pitch) {
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
				static Uint16 *ubuff16 = 0;
				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*2);
				
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
			static Uint32 *ubuff32 = 0;
			ubuff8 = (Uint8*) buff;
			ubuff8 += (y*pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			}
			break;
	}

}

Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 type, Uint16 pitch) {
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

struct mxRGB {
	Uint32 col;
	void operator=(mxRGB &r) {
		this->col = r.col ;
	}
};


struct mxRGB screen[480][272];

void init_screen(SDL_Surface *surf) {
	void *buf = lock(surf, surf->format->BitsPerPixel);
	for(unsigned int i = 0; i < 480; i++)
		for(unsigned int z = 0; z < 272; z++) {
			Uint32 color = getpixel(surf, i,z, surf->format->BitsPerPixel, surf->pitch);
			screen[i][z].col = color;
		}			

	unlock(surf);
}

int movement = 0;

void render(SDL_Surface *surf) {

	static float random = 1.0f;

	void *buf = lock(surf, surf->format->BitsPerPixel);

	for(unsigned int ii = 1; ii < 480-1; ii++) {
		for( unsigned int zz = 1; zz < 272-1; zz++) {
			//mx->SetPixel(mx->GetFront(), ii, zz, mxRGB(mx->GetFront(), Uint8(screen[ii][zz].r * random), Uint8(screen [ii][zz].g * random), Uint8(screen[ii][zz].b * random) ));	
			switch(movement) {
				case 1:
				screen[ii][zz] = screen[zz+1][ii+1];
					break;
				case 2:
					screen[ii][zz] = screen[zz-1][ii-1];
					break;
				case 3:
					screen[ii][zz] = screen[zz+1][ii-1];
					break;
				case 4:
					screen[ii][zz] = screen[zz-1][ii+1];
					break;
			}

			
			setpixel(buf, ii, zz,Uint32(screen[ii][zz].col * random) + rand()%255 ,surf->format->BitsPerPixel, surf->pitch);
		random += 0.0001f;
		if(random > 10) {
			random = 0;
		}
	
		}
	}

	unlock(surf);

	SDL_UpdateRect(surf, 0,0,480,272);
}

extern "C" int SDL_main(int argc, char **argv) {
	SDL_Surface *front = 0, *pic = 0;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;
	front = SDL_SetVideoMode(480,272,0,0);
	if(!front)
		return -1;

	atexit(SDL_Quit);

	SDL_Event e;
	pic = SDL_LoadBMP("fractal.bmp");
	if(!pic)
		fprintf(stderr, "Error couldnt load bitmap");


	init_screen(pic);
	int active = 1;

	Joystick joy(0);

	while(active == 1) {

		render(front);

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
			case SDL_QUIT:
				active = 0;
				break;
			case SDL_JOYBUTTONDOWN:
				switch(e.jbutton.button) 
				{
				case 6: movement = 1; break;
				case 7: movement = 2; break;
				case 8: movement = 3; break;
				case 9: movement = 4; break;
				default:
					movement = 0;
				}
				break;
			}
		}

	}

	SDL_FreeSurface(pic);
	SDL_Quit();
	return 0;
}

