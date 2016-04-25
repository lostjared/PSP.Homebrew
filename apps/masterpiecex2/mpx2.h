#ifndef __MPX2_H__
#define __MPX2_H__

#include "mxfont.h"
#define TILE_W 17
#define TILE_H 25


enum { ID_INTRO, ID_START, ID_GAME, ID_GAMEOVER };

extern SDL_Joystick *stick[2];
extern SDL_Surface *front;
extern SDL_Surface *logo, *start, *gfx[8], *gbg;
extern struct SDL_Font *font;
extern int scr;

extern void render(int screen);
extern void start_game();

typedef struct _Block {
	Uint32 color[3];
	int x,y;
} Block;


typedef struct _Game {
	SDL_Joystick *stick;
	SDL_Rect cords;
	Block gblock;
	Uint32 Tiles[TILE_W][TILE_H];
	int score, lines;
	int player_num;
} mpGame;

extern mpGame game[2], *winner;

extern void init_game();
extern void move_left();
extern void move_right();
extern void render_start();
extern void game_over(mpGame *);

#endif
