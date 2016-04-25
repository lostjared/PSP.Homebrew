#include "smx.h"
#include "level.h"

int shown_logo = 0;
int cl_pos = 0, cl2_pos = 0;
int menu_level = 0;


Uint32 intro_wait(Uint32 i) {
	shown_logo = 1;
	SDL_SetTimer(225, check_start_in);
	return 0;
}

Uint32 check_start_in(Uint32 i) {


	Uint8 *keys = SDL_GetKeyState(0);
	int b = SDL_JoystickGetHat(stick, 0);
	if(keys[SDLK_UP] 
#ifdef FOR_PSP
	|| SDL_JoystickGetButton(stick, 8)
#else
	|| b & SDL_HAT_UP
#endif
		) {
		if(menu_level == 0 && cl_pos > 0)
			cl_pos--;
		if(menu_level == 1 && cl2_pos > 0)
			cl2_pos--;
	}
	else if(keys[SDLK_DOWN] 
#ifdef FOR_PSP
	|| SDL_JoystickGetButton(stick, 6)
#else
	||	b & SDL_HAT_DOWN 
#endif
		) {
		if(menu_level == 0 && cl_pos < 2)
			cl_pos++;
		if(menu_level == 1 && cl2_pos < 1)
			cl2_pos++;
	}

	else if(keys[SDLK_SPACE] || SDL_JoystickGetButton(stick, 2))
	{
		switch(menu_level) {
			case 0:
		switch(cl_pos) {

			case 0:
				menu_level = 1;
				cl2_pos = 0;
				break;
			case 1:
				cur_scr = ID_CREDITS;
				break;
			case 2:
				{		active = 0;

				}
				break;
			}
			break;
		case 1:
			{
					cur_levels = cl2_pos;
					cur_level = 0;
					menu_level = 0;
					reload_level();
					return 0;
			}
			break;
		}
	}



	return i;
}


void render_start() {

	SDL_BlitSurface(logo, 0, front, 0);

	if(shown_logo == 1) {

		SDL_Rect rc = { 50, 50, front->w-100, front->h-100 };
		SDL_FillRect(front, &rc, 0);
		if(menu_level == 0) {
			SDL_PrintText(front, font, 75, 75, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "SuperMasterX-LostSideDead");
			SDL_PrintText(front, font, 125, 175, SDL_MapRGB(front->format, 255, 255, 255), "Single Player ");
			SDL_PrintText(front, font, 125, 175+50, SDL_MapRGB(front->format, 255, 0, 0), "Credits");
			SDL_PrintText(front, font, 125, 175+100, SDL_MapRGB(front->format, 255, 255, 0), "Exit");
			{
				SDL_Rect rc = { 125, front->h-100-hgfx[0]->h , hgfx[0]->w, hgfx[0]->h };
				SDL_SetColorKey( hgfx[0] , SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255, 255, 255));
				SDL_BlitSurface( hgfx[0], 0, front, &rc );
				{
					int cx = 100, cy = 175;
					cy = cy+(50*cl_pos);
					SDL_PrintText( front, font, cx, cy, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "=)>");
				}
			}
		}
		else if(menu_level == 1) {
			SDL_PrintText(front, font, 75, 75, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "SuperMasterX Play New Game");
			SDL_PrintText(front, cfont, 125, 175, SDL_MapRGB(front->format, 255, 255, 255), "New SuperMasterX Levels");
			SDL_PrintText(front, cfont, 125, 175+50, SDL_MapRGB(front->format, 255, 0, 0), " Old SuperMaster2 Levels");
			{
				SDL_Rect rc = { 125, front->h-100-hgfx[0]->h , hgfx[0]->w, hgfx[0]->h };
				SDL_SetColorKey( hgfx[0] , SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255, 255, 255));
				SDL_BlitSurface( hgfx[0], 0, front, &rc );
				{
					int cx = 100, cy = 175;
					cy = cy+(50*cl2_pos);
					SDL_PrintText( front, font, cx, cy, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "=)>");
				}
			}

		}
	}


}

void check_enter_in() {
	Uint8 *keys = SDL_GetKeyState(0);
#ifdef FOR_PSP
	if(SDL_JoystickGetButton(stick, 11))
#else
	if(keys[SDLK_RETURN] || SDL_JoystickGetButton(stick, 1))
#endif
	{	cur_scr = ID_GAME; 	

	SDL_SetTimer(75,proccess_game );

#ifdef FOR_PSP
	SDL_SetTimer(25, proccess_game);
#endif
#ifdef FOR_XBOX_OPENXDK
	SDL_SetTimer(125, proccess_game);
#endif

	}



}

void render_enter_level() {

	SDL_BlitSurface(bg, 0, front, 0);
	{
		SDL_Rect rc = { 50, 50, 640-100, 480-100 };
		SDL_Rect rc2 = { 100, 100, hgfx[0]->w, hgfx[0]->h };
		SDL_FillRect( front, &rc, 0);
		SDL_SetColorKey(hgfx[0] , SDL_SRCCOLORKEY, SDL_MapRGB(hgfx[0]->format, 255, 255, 255));
		SDL_BlitSurface( hgfx[0] , 0, front, &rc2 );
		{
			static char sbuf[256], lifebuf[256];
			sprintf(sbuf, "Now Entering Level %s", level->level_name);
			sprintf(lifebuf, "Lives: %d", lives);
			SDL_PrintText(front, font, 150, 100, SDL_MapRGB(front->format, 255, 255, rand()%255), sbuf);
			SDL_PrintText(front, cfont, 150, 175, SDL_MapRGB(front->format, 255, 255, 255), lifebuf);
			SDL_PrintText(front, font, 150, 200, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "Press Start to Play Level");
			{
				SDL_Rect rc4 = { 0, 480-lsd->h, lsd->w, lsd->h };
				SDL_BlitSurface( lsd, 0, front, &rc4 );

			}
		}
	}

	check_enter_in();

}

static void credits_in() {

	Uint8 *keys = SDL_GetKeyState(0);
	
#ifdef FOR_PSP
	if( SDL_JoystickGetButton(stick, 11) )
#else
	if(keys[SDLK_RETURN] || SDL_JoystickGetButton(stick, 1))
#endif

		cur_scr = ID_START;

}

void render_credits() {
			int i,z;
			void *buf, *buf2, *buf3;
			static float alpha = 0.0f;

			credits_in();
			if(cur_scr == ID_START)
				return;

			buf = lock(front, front->format->BitsPerPixel);
			buf2 = lock(logo, front->format->BitsPerPixel);
			buf3 = lock(bg,   front->format->BitsPerPixel);

			for(i = 0; i < front->w; i++) {
				for(z = 0; z < front->h; z++) {
					SDL_Color col1, col2;
					Uint32 color;
					getpixel(logo, i, z, logo->format->BitsPerPixel, logo->pitch, &col1);
					getpixel(bg, i, z, bg->format->BitsPerPixel, bg->pitch, &col2);
					color = SDL_MapRGB(front->format, ((Uint8)(alpha * col1.r) + (1-alpha) * col2.r), (Uint8)(alpha * col1.g) + (1-alpha) * col2.g , (Uint8) (alpha * col1.b) + (1-alpha) * col2.b);
					if((rand()%2) == 0) color += (int)sinf(alpha) * col1.r / (1+col2.g); else color -= (int) cosf(alpha) * col1.b / (1+col1.r);
					setpixel(buf, i, z, color, front->format->BitsPerPixel, front->pitch);
				}

			}


			unlock(front);
			unlock(logo);
			unlock(bg);

			alpha += 0.1f;
			if(alpha > 8.0f)
				alpha = 0.0f;
			{
				SDL_Rect rc = { 100, 300, 640-200, 100 };
				SDL_Rect rcX = { 125, 315, hgfx[4]->w, hgfx[4]->h };

				SDL_FillRect(front, &rc, 0);
				SDL_SetColorKey(hgfx[4], SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255, 255, 255));
				SDL_BlitSurface( hgfx[4], 0, front, &rcX);
				{
					SDL_Rect rcY = { 0, 0, evil_gfx[0].gfx[0]->w, evil_gfx[0].gfx[0]->h };
					SDL_Rect rcZ = { 640-120-evil_gfx[0].gfx[0]->w, 315, evil_gfx[0].gfx[0]->w, evil_gfx[0].gfx[0]->h };
					SDL_ReverseBlt(evil_gfx[0].gfx[0], &rcY, front, &rcZ, SDL_MapRGB(front->format, 255, 255, 255));

				}
				SDL_PrintText(front, font, 170, 360, SDL_MapRGB(front->format, 255, 255, 255), "SuperMasterX - LostSideDead");
				SDL_PrintText(front, cfont, 170, 380, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "\"Open Source, Open Mind\"");

			}
				
			

}
