#include "level.h"
#include "smx.h"
#ifdef FOR_PSP
#include <pspkerneltypes.h>	//# |_ For 333Mhz Overclock
#include <psppower.h>		//# |
#endif


#ifdef FOR_PSP
Mix_Chunk *intro_snd = 0, *collect_snd = 0, *fire_snd = 0, *kill_snd = 0;
Mix_Music *game_track;
#endif

struct SDL_Font *font = 0, *cfont = 0;

int cur_scr = ID_ENTER;
SDL_Surface *front = 0;
SDL_Surface *gfx[16], *hgfx[12], *particles[4], *bg, *collect[8], *lsd, *logo;
static char *img_str[] = { "black.bmp", "grass.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp",
"snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", "black.bmp",
0 };
static char *hstr[] = { "hero1.bmp", "hero2.bmp", "hero3.bmp", "hero4.bmp", "hero_jump1.bmp", "hero_shot1.bmp", "hero_shot2.bmp", "hero_shot3.bmp", "hero_shot4.bmp", 0 };
static char *ev[] = { "img/grandma/", 0 };
SDL_Joystick *stick = 0;
Emiter emiter;
int custom_level = 0;
char custom_lvl[256];
int cur_level = 0;
int score = 0, lives = 0;
int active = 1;
int cur_levels = 0;

static char *level_str[] = { "", "SuperMaster2/", 0 };

void reload_level() {
	char sbuf[256];
	SDL_FillRect(front, 0, 0);
	SDL_PrintText(front, font, 25, 25, SDL_MapRGB(front->format, 255, 0, 0), "Loading...");
	SDL_Flip(front);
	if(cur_level >= 8)
		cur_level = 0;

	if(custom_level == 0)
	sprintf(sbuf,"%slevel/level%d.sml", level_str[cur_levels], ++cur_level);
	else
	sprintf(sbuf, custom_lvl);

	if(level != 0) release_level(level);
	level = load_level(sbuf);

	hero.hpos = level->start_pos;
	srand((unsigned int) SDL_GetTicks() );

	{
		unsigned int i = 0;

		for(i; i < 50; i++) {
			if(level->items[i].type != 0) do { level->items[i].type = rand()%COLLECT_NUM; } while( level->items[i].type == 0 );
		}
	}
	offset = 0;
	init_particles(&emiter);
	cur_scr = ID_ENTER;
	
}

void init_game() {
	score = 0, lives = 10;
	cur_level = 0;
	reload_level();
	cur_scr = ID_START;
	SDL_SetTimer(225, check_start_in);

}
		
static void init() {

	Uint8 i = 0;

	font = SDL_InitFont(get_path("D:\\", "font/system.mxf"));
	cfont = SDL_InitFont(get_path("D:\\", "font/e.mxf"));
	SDL_FillRect(front, 0, 0);
	SDL_PrintText(front, font, 25, 25, SDL_MapRGB(front->format, 255, 255, 255), "Loading..");
	SDL_Flip(front);
	init_game();
	SDL_SetTimer(1000, intro_wait);
	SDL_FillRect(front, 0, 0);
	SDL_PrintText(front, font, 25, 25, SDL_MapRGB(front->format, 255, 255, 255), "Loading.. Bitmaps");
	SDL_Flip(front);

	particles[0] = SDL_LoadBMP(get_path("D:\\", "img/shot.bmp"));
	lsd = SDL_LoadBMP(get_path("D:\\", "img/lsd.bmp"));
	logo = SDL_LoadBMP(get_path("D:\\", "img/logo.bmp"));
	for(i = 0; img_str[i] != 0; i++) {
		static char sbuf[256];
		sprintf(sbuf, "img/%s", img_str[i]);
		gfx[i] = SDL_LoadBMP(get_path("D:\\", sbuf));
		if(!gfx[i])
			fprintf(stderr, "Error couldnt load graphic %s\n", sbuf);
	}
	for(i = 0; hstr[i] != 0; i++) {
		static char sbuf[256];
		sprintf(sbuf, "img/hero/%s", hstr[i]);
		hgfx[i] = SDL_LoadBMP(get_path("D:\\", sbuf));
		if(!hgfx[i])
			fprintf(stderr, "Error couldnt load graphic %s\n", sbuf);
	}

	for(i = 0; i < COLLECT_NUM; i++) {
		static char sbuf[256];
		sprintf(sbuf, "img/col%d.bmp", i+1);
		collect[i] = SDL_LoadBMP(get_path("D:\\", sbuf));
		if(!collect[i])
			fprintf(stderr, "Error couldnt load graphic %s\n", sbuf);
	}

	{
		

		for( i = 0; ev[i] != 0; i++ ) {

			unsigned int z;

			for( z = 0; z < 10; z++ ) {
				static char sbuf[256];
				memset(sbuf, 0, sizeof(sbuf));
				sprintf(sbuf,"%sevil%d.bmp", ev[i], z+1);
				evil_gfx[i].gfx[z] = SDL_LoadBMP(get_path("D:\\", sbuf));
				if(!evil_gfx[i].gfx[z])
					fprintf(stderr, "Couldnt load %s ", sbuf);
			}

			evil_gfx[i].type = i;
		}
	}

	SDL_FillRect(front, 0, 0);
	SDL_PrintText(front, cfont, 25, 25, SDL_MapRGB(front->format, 0, 0, 255), "Loading Sound Effects...");
	SDL_Flip(front);
	bg = SDL_LoadBMP(get_path("D:\\", "img/bg.bmp"));
	
	#ifdef FOR_PSP
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	intro_snd = Mix_LoadWAV(get_path("D:\\", "snd/open.wav"));
	collect_snd = Mix_LoadWAV(get_path("D:\\", "snd/line.wav"));
	fire_snd = Mix_LoadWAV(get_path("D:\\", "snd/fire.wav"));
	kill_snd = Mix_LoadWAV(get_path("D:\\", "snd/scream.wav"));
	//game_track = Mix_LoadMUS(get_path("D:\\", "snd/theme.ogg"));
	#endif

	
	
	SDL_FillRect(front, 0, 0);
	SDL_PrintText(front, font, 25, 25, SDL_MapRGB(front->format, 255, 255, 255), "Loading.. Done");
	SDL_Flip(front);

#ifdef FOR_PSP
	if(intro_snd != 0)
	Mix_PlayChannel( -1, intro_snd, 0);
	if(game_track != 0);
	//Mix_PlayMusic(game_track, -1);
#endif


}

static void rls() {

	Uint8 i = 0, z = 0;

	for( i = 0; img_str[i] != 0; i++)
		SDL_FreeSurface(gfx[i]);
	for( i = 0; hstr[i] != 0; i++)
		SDL_FreeSurface(hgfx[i]);
	for ( i = 0; ev[i] != 0; i++) 
		for(z = 0; z < 10; z++)
			SDL_FreeSurface(evil_gfx[i].gfx[z]);

	for( i = 0; i < COLLECT_NUM; i++)
		SDL_FreeSurface(collect[i]);

	SDL_FreeSurface(bg);
	SDL_FreeSurface(particles[0]);
	SDL_FreeSurface(front);
	SDL_FreeSurface(lsd);
	SDL_FreeSurface(logo);
	SDL_FreeFont(cfont);
	SDL_FreeFont(font);
	release_level(level);

#ifdef FOR_PSP
	Mix_FreeChunk(fire_snd);
	Mix_FreeChunk(collect_snd);
	Mix_FreeChunk(intro_snd);
	Mix_FreeChunk(kill_snd);
	//Mix_FreeMusic(game_track);
	Mix_HaltMusic();
	Mix_CloseAudio();
#endif

}

static void render() {
	switch(cur_scr) {
		case ID_GAME:
		render_map(front, level);
		break;
		case ID_ENTER:
		render_enter_level();
		break;
		case ID_START:
		render_start();
		break;
		case ID_CREDITS:
		render_credits();
		break;
		case ID_PAUSED:
		render_pause();
		break;
	}
}

#ifdef FOR_XBOX_OPENXDK
void XBoxStartup() {
	char **argv = 0;
	int argc = 0;
#else
int main(int argc, char **argv) {
#endif
	Uint32 mode = 0;
	SDL_Surface *ico = 0;


	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0)
		return -1;

#ifdef FOR_PSP
	scePowerSetClockFrequency(333, 333, 166); //# overclocked
#endif


	SDL_ShowCursor(SDL_FALSE);
	ico = SDL_LoadBMP(get_path("D:\\", "img/col1.bmp"));
	SDL_WM_SetIcon(ico, 0);
	if(argc == 2 && strcmp(argv[1], "--full") == 0)
		mode = SDL_FULLSCREEN;

	if(!(front = SDL_SetVideoMode(640,480,0,mode)))
		return -1;

	SDL_WM_SetCaption(" SuperMasterX ", 0);
	SDL_JoystickEventState(SDL_ENABLE);
	stick = SDL_JoystickOpen(0);

	if(argc == 3 && strcmp(argv[1], "--run") == 0)
	{
		//custom_level = 1;
		memset(custom_lvl, 0, sizeof(custom_lvl));
		strcpy(custom_lvl, argv[2]);
		{ // Test to see if file Exisits
			FILE *fptr = fopen(custom_lvl, "r");
			if(!fptr)
			{
				// nope dosent exisit
				custom_level = 0;
				fprintf(stderr, "Error level map %s not found!", custom_lvl);
			} else {
				custom_level = 1;
				fclose(fptr);
			}
		}
	}
	init();
	{
		
		static SDL_Event e;

		while(active == 1) {

			SDL_FillRect(front, 0, 0);
			render();
			if(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:
						active = 0;
						break;
					case SDL_KEYDOWN:
						{
							switch(e.key.keysym.sym) {
							case SDLK_ESCAPE:
								active = 0;
								break;
							case SDLK_LEFT:
							//	scroll_left();
								break;
							case SDLK_RIGHT:
							//	scroll_right();
								break;
							}
						}
						break;
				}
			}

			SDL_Flip(front);
		}


	}
	rls();
	SDL_FreeSurface(ico);
	SDL_FreeSurface(front);
	SDL_JoystickClose(stick);
	SDL_Quit();
	return 0;
}

void SDL_ReverseBlt(SDL_Surface *surf, SDL_Rect *rc, SDL_Surface *front_surf, SDL_Rect *rc2, Uint32 transparent) {

	void *buf , *buf2;
	int i,z,i2,z2;
	buf = lock(surf, surf->format->BitsPerPixel);
	buf2 = lock(front_surf, front_surf->format->BitsPerPixel);

	i2 = rc2->x;
	z2 = rc2->y;

	for(i = rc->w; i > 0; i--) {
		for(z = 0; z < rc->h; z++) {
			SDL_Color col;
			Uint32 color = getpixel(surf, i, z, surf->format->BitsPerPixel, surf->pitch, &col);
			if(color != transparent)
			setpixel(buf2, i2, z2, SDL_MapRGB(front_surf->format, col.r, col.g, col.b), front_surf->format->BitsPerPixel, front_surf->pitch);
			z2++;

		}
		z2 = rc2->y;
		i2++;
	}
}

int SDL_Colide(SDL_Rect *rc, SDL_Rect *rc2) {

	int i,z;

	if(!(rc->x > 0 && rc->x+rc->w < 640 && rc->y > 0 && rc->y+rc->h < 480))
		return 0;

	for( i = rc->x; i < rc->x+rc->w; i++) {
		for(z = rc->y; z < rc->y+rc->h; z++) {
			if(i >= rc2->x && i <= rc2->x+rc2->w && z >= rc2->y && z <= rc2->y+rc2->h) return 1;
		}

	}
	return 0;
}

const char *get_path(char *p, char *s) {
	static char sbuf[256];
#ifdef FOR_XBOX_XDK
	sprintf(sbuf, "%s%s", p, s);
	return sbuf;
#endif
	sprintf(sbuf, "%s", s);
	return sbuf;
}