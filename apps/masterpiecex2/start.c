#include "mpx2.h"
#include<stdlib.h>


static void chk_in() {

	int i = 0, z = 0;

	for(i = 0; i < 2; i++) {
		for( z = 0; z < 12; z++) {
			if(SDL_JoystickGetButton(game[i].stick, z))
			{
				start_game();
				scr = ID_GAME;
			}
		}
	}


}

void render_start() {


	SDL_BlitSurface(gbg, 0, front, 0);
	{
		SDL_Rect rc = { 25, 100, 640-50, 480-200 };
		SDL_FillRect(front, &rc, 0);
		SDL_PrintText(front, font, rc.x+25, rc.y+25, SDL_MapRGB(front->format, 255, 0, 0), "MasterPieceX2 ");
		SDL_PrintText(front, font, rc.x+25, rc.y+60, SDL_MapRGB(front->format, 255, 255, 255), "Press Start to Play");
		{
			int i,z;
			void *buf, *buf2, *buf3;

			buf = lock(front, front->format->BitsPerPixel);
			buf2 = lock(logo, front->format->BitsPerPixel);
			buf3 = lock(gbg, front->format->BitsPerPixel);

			for(i = rc.x+25; i < 640-50-25; i++) {
				for(z = rc.y+80; z < 480-200-25; z++) {
					SDL_Color col1, col2;
					static float alpha = 0.0f;
					Uint32 color;
					alpha += 0.1f;
					if(alpha > 1.0f)
						alpha = 0.0f;
					getpixel(logo, i, z, logo->format->BitsPerPixel, logo->pitch, &col1);
					getpixel(gbg, i, z, gbg->format->BitsPerPixel, gbg->pitch, &col2);
					color = SDL_MapRGB(front->format, ((Uint8)(alpha * col1.r) + (1-alpha) * col2.r), (Uint8)(alpha * col1.g) + (1-alpha) * col2.g , (Uint8) (alpha * col1.b) + (1-alpha) * col2.b);
					setpixel(buf, i, z, color, front->format->BitsPerPixel, front->pitch);

				}

			}
			unlock(front);
			unlock(logo);
			unlock(gbg);
		}

	}

	chk_in();
}

