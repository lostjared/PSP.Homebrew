#include"mpx2.h"
#include "platform.h"


SDL_Joystick *stick[2];

SDL_Surface *front = 0;
struct SDL_Font *font = 0;
static char *file_path = "D:\\";
SDL_Surface *logo, *start, *gbg, *gfx[8];

static const char *get_path(const char *path, const char *file) {
	static char cbuf[256];
	sprintf(cbuf,"%s%s", path, file);
#ifdef FOR_PC
	sprintf(cbuf, "%s", file);
#endif
#ifdef FOR_XBOX_OPENXDK
	sprintf(cbuf, "%s", file);
#endif

	return cbuf;
}

static void init() {
	font = SDL_InitFont(get_path("D:\\", "font\\system.mxf"));
	logo = SDL_LoadBMP(get_path("D:\\", "img\\logo.bmp"));
	start = SDL_LoadBMP(get_path("D:\\", "img\\start.bmp"));
	gbg = SDL_LoadBMP(get_path("D:\\", "img\\background.bmp"));

	{
		static char sbuf[256];
		int i;
		for(i = 0; i < 8; i++) {
			sprintf(sbuf, "img\\block%d.bmp", i+1);
			gfx[i] = SDL_LoadBMP(get_path("D:\\", sbuf));
		}
	}

	init_game();
	SDL_WM_SetCaption("MasterPiece X2", 0);

}

static void clr() {
	SDL_FreeFont(font);
	SDL_FreeSurface(logo);
	SDL_FreeSurface(start);
	SDL_FreeSurface(gbg);
	{
		int i;
		for(i = 0; i < 8; i++) {
			SDL_FreeSurface(gfx[i]);
		}
	}
}

#ifdef FOR_XBOX_OPENXDK
void XBoxStartup() {
int argc = 0;
char **argv = 0;

#else
int main(int argc, char **argv) {
#endif

	SDL_Surface *ico = 0;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0)
		return -1;

	
	ico = SDL_LoadBMP(get_path("D:\\", "img\\ico.bmp"));

	SDL_WM_SetIcon(ico, 0);
	SDL_ShowCursor(SDL_FALSE);


	if(argc >= 2 && strcmp(argv[1], "--full") == 0)
		front = SDL_SetVideoMode(640,480,0,SDL_FULLSCREEN | SDL_DOUBLEBUF);
	else
		front = SDL_SetVideoMode(640,480,0,0);
	if(!front)
		return -1;

	SDL_JoystickEventState(SDL_ENABLE);
	stick[0] = SDL_JoystickOpen(0);
	stick[1] = SDL_JoystickOpen(1);
	init();
	{
		static SDL_Event e;
		int active = 1;
		while(active == 1) {

			SDL_FillRect(front, 0, 0);
			render(scr);
			if(SDL_PollEvent(&e)) {
				switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;

				case SDL_JOYHATMOTION:
					{

					}
					break;
				case SDL_KEYDOWN:
					{
						if(e.key.keysym.sym == SDLK_ESCAPE)
							active = 0;
					}
					break;
				}
			}
			SDL_Flip(front);
		}
	}
	clr();
	SDL_FreeSurface(ico);
	SDL_JoystickClose(stick[0]);
	SDL_JoystickClose(stick[1]);
	SDL_FreeSurface(front);
	SDL_Quit();
	return 0;

}

