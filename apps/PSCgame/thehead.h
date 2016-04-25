#ifndef __THEHEAD__H_
#define __THEHEAD__H_

#include<SDL.h>
//#include<SDL_ttf.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//#include<memory.h>
#include <SDL_mxf.h>

struct array_buffer {
	int x,y;
	int active,type;
	struct array_buffer *next;
};

struct cannon {
	int x,y;
};


extern SDL_Surface *cd,*coin,*psc,*cannon,*logo;
extern SDL_Surface *front;
extern int move_dir, score, miss, screen;
extern SDL_Joystick *init_joy(int num);
extern SDL_Joystick *joy;
extern int cd_count, the_fire;
extern struct array_buffer *buff;
extern struct cannon the_can;
extern void render();
extern void load();
extern void unload();
extern void printtextf(struct SDL_Font *fnt,int x, int y, SDL_Color col, const char *src, ...);
extern void init_buffer(struct array_buffer *buff, int type);
extern struct array_buffer *add_item_to_buffer(struct array_buffer *node, int type);
extern void proccess_nodes(struct array_buffer *node);
extern void new_game();
extern void free_nodes(struct array_buffer *node);
extern void reset_node(struct array_buffer *node);
extern void dump_buffer(struct array_buffer *node);
extern void rls_cash(struct array_buffer *node);
//extern Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 type, Uint16 pitch);
#endif
