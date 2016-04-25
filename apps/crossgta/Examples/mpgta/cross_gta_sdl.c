#include "cross_gta.h"

#include<SDL.h>

SDL_Surface *front = 0;
SDL_Joystick *stick = 0;

void init_app() {

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return ;

	front = SDL_SetVideoMode(480,272,0,0);
	if(!front)
		return;

	stick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);

}

void loop(void (*render)(), void (*joy_down)(int button)) {


	SDL_Event e;
	int active = 1;

	while(active == 1) {

		SDL_FillRect(front, 0,0);
		render();

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
				case SDL_JOYBUTTONDOWN:
					{
						joy_down(e.jbutton.button);
					}
					break;
				case SDL_KEYDOWN:
					{
						switch(e.key.keysym.sym)
						{
						case SDLK_LEFT:
							joy_down(7);
							break;
						case SDLK_RIGHT:
							joy_down(9);
							break;
						case SDLK_DOWN:
							joy_down(6);
							break;
						case SDLK_a:
							joy_down(0);
							break;
						case SDLK_s:
							joy_down(1);
							break;
						}
	                }
					break;
			}
		}
		swap_buffer();
	}


}

void clean_app() {
	SDL_JoystickClose(stick);
	SDL_FreeSurface(front);
	SDL_Quit();
}

void swap_buffer() {
	SDL_UpdateRect(front, 0,0,480,272);
}

/* from pixelbuffer.c ---****************************************************  */
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
/* ----------------- end from pixelbuffer */


void set_pixel(int x, int y, unsigned long color) {
	void *buf = lock(front, front->format->BitsPerPixel);
	if(x > 0 && x < 480 && y > 0 && y < 272)
	setpixel(buf, x, y, color, front->format->BitsPerPixel, front->pitch);
	unlock(front);
}

int draw_text(unsigned int *fnt_ptr,int font_w, int font_h,  int x, int y, unsigned long color, char *src) {
	int prev_x = x;
	int offset_x = prev_x, offset_y = y;
	int width = 0, height = 0;
	int i,z,p;

	for(p = 0; p < (int)strlen(src);  p++) {
		unsigned int *ptr = fnt_ptr;
		if(src[p] == '\n') {
			offset_x = prev_x;
			offset_y += height;
			continue;
		}
		
		ptr += (src[p] * (font_w*font_h));
			
		for(i = 0; i < font_w; i++) {
			for(z = 0; z < font_h; z++) {
			
				if((*ptr)) {
					if(offset_y+z > 0 && offset_x+i > 0 && offset_y+z < 272 && offset_x+i < 480)
					set_pixel(offset_x+i, offset_y+z, color);
					width=i;
					if(height < z)
						height=z;
				}
				ptr++;
			}
		}
		offset_x += width;
		if(offset_x+width >= 480) {
			offset_x = prev_x;
			offset_y += height;
		}
		if(offset_y+height > 272)
				return 1;
					
	}

	return 0;
}

int draw_int(unsigned int *fnt_ptr, int font_w, int font_h, int x, int y, unsigned long color, unsigned long val) {

	unsigned long divisor = 10000000L;
	unsigned char nibble;
	unsigned char data_buf[15];
	int index = 0;

	val = val % 100000000L;

	while (divisor > 0)
	{
		nibble = val / divisor;
		data_buf[index++] = nibble+'0';
		val = val - (nibble * divisor);
		x++;
		divisor /= 10;
	}

	data_buf [index] = 0;
	draw_text(fnt_ptr, font_w, font_h, x,y,color, data_buf);
	return 0;
}

void fill_rect(int x, int y, int w, int h, unsigned long color) {
	SDL_Rect rc = { x,y,w,h };
	SDL_FillRect(front, &rc, color);
}
// begin helper functions
int GetFX(int mx,int x, int nw) {
	float xp = (float)x * (float)mx / (float)nw;		
	return (int)xp;
}

int GetFZ(int my, int y, int nh) {
	float yp = (float)y * (float)my / (float)nh;
	return (int)yp;
}
// end helper functions

void draw_bitmap(unsigned long *raw_bits,  int x, int y, int w, int h, int orig_w, int orig_h, unsigned long ckey) {
	int i,z;

	for(i = 0; i < w; i++)
		for(z = h; z > 0; z--) {
			int pos_x = GetFX(orig_w,i,w);
			int pos_y = GetFZ(orig_h,z,h);
			if(raw_bits[pos_x+pos_y*w] != ckey)
			set_pixel(i+x,z+y, raw_bits[pos_x+pos_y*w]);
		}

}

unsigned long map_rgb(unsigned char r, unsigned char g, unsigned char b) {
	//return ((unsigned long)(((unsigned char)(r)|((unsigned int)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)));
	return ((unsigned long)(((unsigned char)(b)|((unsigned int)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(r))<<16)));
}

int main(int argc, char **argv) {
	Main();
	return 0;
}
