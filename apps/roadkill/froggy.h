#ifndef __FROGGER_H_
#define __FROGGER_H_

#include<stdio.h>
#include<SDL.h>
#include<SDL_mxf.h>



extern SDL_Surface *front;
extern SDL_Surface *cars[11];
extern int level_speed;
extern struct SDL_Font *font;
extern int scr;
extern SDL_Joystick *stick;


extern void render();
extern void init();
extern void free_gfx();
extern void new_game();
extern void SDL_ReverseBlt(SDL_Surface *surf, SDL_Rect *rc, SDL_Surface *front_surf, SDL_Rect *rc2, Uint32 transparent);

#endif

