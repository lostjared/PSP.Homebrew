#include<SDL.h>
#include<stdlib.h>
#include"dirbrowse.h"

#include <pspkerneltypes.h>	//# |_ For 333Mhz Overclock
#include <psppower.h>		//# |

struct SDL_Font *the_font = 0;
SDL_Surface *bg = 0;

struct Letter {
	int x,y;
	int speed;
	char c[30];
	Uint32 color;
};

struct Letter letters[50];

char randletter(int max) {
	char c;
	do {
		c = rand()%max;
	} while( c > 33 && c < 128 );
	return c;
}

void init_letters(SDL_Surface *surf) {
	int i,z;
	for(i = 0; i < 50; i++) {
		for(z = 0; z < 30; z++)
		letters[i].c[z] = randletter(128);
		letters[i].x = i*14;
		letters[i].y = -30*12;
		do 
		letters[i].speed = 1+rand()%10;
			while(letters[i].speed <= 0);
		letters[i].color = SDL_MapRGB(surf->format, rand()%255, rand()%255, rand()%255);
	}
}

SDL_Surface *fill_background(SDL_Surface *surf) {
	
	void *buf;
	int i = 0, z = 0;
	float rand_r = 0.1f;
	static int rand_movement = 1, wait = 0;
	buf = lock(surf, surf->format->BitsPerPixel);

	
	for(i = 1; i < surf->w-1; i++)
		for(z = 1; z < surf->h-1; z++)
		{
			SDL_Color col;
			setpixel(buf, i,z, getpixel(surf, i, z, surf->format->BitsPerPixel, surf->pitch, &col)+rand_r, surf->format->BitsPerPixel, surf->pitch);
			if(rand()%2 > 0) rand_r += 0.1f; else rand_r -= 0.2f;
		}
	
	wait ++;
	if(wait > 25)// 25 frames have passed
	{
		rand_movement = !rand_movement;
		wait = 0;
	}

	unlock(surf);

	return surf;
}

void draw(SDL_Surface *surf) {
	int i,z;
	static float color_r = 0.1f;
	for(i = 0; i < 50; i++)
	{
		
		for(z = 0; z < 30; z++) {
			char buf[2];
			buf[0] = letters[i].c[z];
			buf[1] = 0;
			if(letters[i].y+(z*12) > 0)
			SDL_PrintText(surf, the_font, letters[i].x, letters[i].y+(z*12), letters[i].color+color_r, buf);
			color_r += 0.1f;
		}

		if(letters[i].y < surf->h)
			letters[i].y += letters[i].speed;

		if(letters[i].y >= surf->h) {
			letters[i].y = -30*12;
			do
			letters[i].speed = 1+rand()%10;
			while (letters[i].speed <= 0);
		}
	}

	if(color_r > 255)
		color_r = 0;

}

int SDL_main(int argc, char **argv) {

	SDL_Surface *front = 0;
	int active = 1;
	int select = 1;
	SDL_Event e;
	SDL_Joystick *joy = 0;
	struct directory_browser b;

	

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;

	if(!(front = SDL_SetVideoMode(480,272,0,0)))
		return -1;


	the_font = SDL_InitFont("font.mxf");
	if(!the_font)
		return -1;

	joy = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
	scePowerSetClockFrequency(333, 333, 166); //# overclocked


	b.x = 10;
	b.y = 10;
	b.w = 460;
	b.h = 265;
	b.cur_i = 0;
	b.max_col = 8;

	b.head = ls2link("./", &b.length);
	init_letters(front);
	bg = SDL_LoadBMP("background.bmp");

	while(active == 1) {

		static SDL_Surface *surf = 0;
		SDL_FillRect(front, 0, 0);
		if(select == 1) {
			draw_browser(front, &b, the_font);
		}
		else {
			surf = fill_background(bg);
			SDL_BlitSurface(surf, 0, front, 0);
			draw(front);
		}
		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
				case SDL_JOYBUTTONDOWN:
					{
						if(select == 0)
						{
							select = 1;
							continue;
						}
						switch(e.jbutton.button) {
						case 8: // move up
							if(b.cur_i > 0)
								b.cur_i--;
							break;
						case 6:// move down
							if(b.cur_i+1 < b.length)
								b.cur_i++;
							break;
						case 7:// move left
							if(b.cur_i+1-b.max_col > 0)
								b.cur_i -= b.max_col;
							break;
						case 9://move right
							if(b.cur_i+b.max_col < b.length)
								b.cur_i += b.max_col;
							break;
						case 0:
						case 1:
						case 2:
						case 3:
							{
								if(select == 1)
								{
								struct file_node *pnode = skip_nodes(b.head->next, b.cur_i);
								if(pnode != 0 && pnode->is_dir == 1) {
									char buf[1000];
									sprintf(buf,"./%s/", pnode->name);
									struct file_node *new_nodes = ls2link(buf, &b.length);
									free_nodes(b.head);
									b.cur_i = 0;
									b.head = new_nodes;
								}
								else if(pnode != 0 && pnode->is_dir == 0) { // its a file
									if(strstr(pnode->name, ".bmp")) {
										if(bg != 0)
										{
											SDL_FreeSurface(bg);
										}
										
										bg = SDL_LoadBMP(pnode->name);

										if(!bg)
										{
											select = 1;

										} else select = 0;
									}
								}
								}
							}

							break;
						}
					}
					break;
			}
		}

		SDL_UpdateRect(front, 0, 0, 480, 272);

	}


	SDL_FreeSurface(bg);
	SDL_FreeFont(the_font);
	SDL_FreeSurface(front);
	SDL_JoystickClose(joy);
	SDL_Quit();

	return 0;
}