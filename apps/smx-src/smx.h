#ifndef __SMX__H_
#define __SMX__H_

#include<SDL_mxf.h>
#include<stdio.h>

#ifndef __INCLUDED_PLATFORM_INFO__
#define __INCLUDED_PLATFORM_INFO__
#include "platform.h"
#endif
#define COLLECT_NUM 6
enum { ID_ENTER = 1, ID_GAME, ID_START , ID_CREDITS, ID_GAMEOVER , ID_PAUSED };

extern SDL_Surface *gfx[16], *front, *hgfx[12], *particles[4], *bg, *collect[8], *lsd, *logo;
extern struct SDL_Font *font, *cfont;
extern SDL_Joystick *stick;
extern int score, lives;
extern void SDL_ReverseBlt(SDL_Surface *surf, SDL_Rect *rc, SDL_Surface *front_surf, SDL_Rect *rc2, Uint32 transparent);
extern int SDL_Colide(SDL_Rect *rc, SDL_Rect *rc2);
extern void init_game();
extern void game_over();
extern void render_enter_level();
extern void render_credits();
extern void render_pause();
extern const char *get_path(char *p, char *s);
extern Uint32 intro_wait(Uint32 i);
extern Uint32 check_start_in(Uint32);
extern int cur_scr, active, cur_levels;
extern int custom_level;
extern char custom_lvl[256];

#ifdef FOR_PSP
#include<SDL_mixer.h>
extern Mix_Chunk *intro_snd , *collect_snd, *fire_snd, *kill_snd;
extern Mix_Music *game_track;
#endif


#endif