#ifndef LEVEL_H__
#define LEVEL_H__

#include<SDL_mxf.h>
#include<stdio.h>
#define MAX_TILE 8000

// game Level structure
typedef struct _Level
{
	struct Tile {
		int block;
		Uint8 solid;
	};
	char level_name[255];
	int grandma[50]; 
	int start_pos;
	struct Tile tiles[MAX_TILE];
	struct Item {
		int vpos,type;
	} items[50];

} Level;


typedef struct _Hero {
	int hpos;
	int x,y,cur_ani,dir;
} Hero;

typedef struct _EvilGfx {
	SDL_Surface *gfx[10];
	int type;
} EvilGfx;

typedef struct _Evil {
	int vpos,x,y,cur_ani,dir,type,die;
	EvilGfx *egfx;
} Evil;

typedef struct _Particle {
	int x,y,type;
	int vpos,dir;
} Particle;

#define MAX_PARTICLE 10

typedef struct _Emiter {
	Particle p[MAX_PARTICLE];
} Emiter;

extern int offset;
extern Level *level;
extern Emiter emiter;
extern Hero  hero;
extern Evil evil[50];
extern EvilGfx evil_gfx[4];
extern int cur_level;
extern Level *load_level(const char *src);
extern void release_level(Level *);
extern void render_map(SDL_Surface *surf, Level *lvl);
extern void scroll_left();
extern void scroll_right();
extern Uint32 proccess_game(Uint32 interval);
extern void reload_level();
extern void init_particles(Emiter *);
extern void proc_particles(Emiter *);
extern void rls_particle(Emiter *, int vpos, int type, int dir);
#endif

