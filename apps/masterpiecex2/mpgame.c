#include "mpx2.h"
#include<stdlib.h>


int scr = ID_INTRO;
mpGame game[2];

Uint32 color_map[8];

static void rand_block(Block *);

int bounds(int x, int y) {
	if(x >= 0 && y >= 0)
		return 1;
	return 0;
}

static void addline(mpGame *g) {

	g->score += 10;
	g->lines++;

}

static void proc_blocks(mpGame *g) {

	int i,z;
	for(i = 0; i < TILE_W; i++) {
		for(z = 0; z < TILE_H-1; z++) {

			if(g->Tiles[i][z] != 0 && g->Tiles[i][z+1] == 0) {
				g->Tiles[i][z+1] = g->Tiles[i][z];
				g->Tiles[i][z] = 0;
			}
		}
	}

}


void proccess_move_down(mpGame *g) {

	int i,z;

	for(i = 0; i < TILE_W; i++) {
		for(z = 0; z < TILE_H; z++) {
			int c = g->Tiles[i][z];
			if(c != 0) {
				if(c == g->Tiles[i][z+1] && c == g->Tiles[i][z+2]) {
					g->Tiles[i][z] = 0;
					g->Tiles[i][z+1] = 0;
					g->Tiles[i][z+2] = 0;
					addline(g);
					return;
				}

				if(c == g->Tiles[i+1][z] && c == g->Tiles[i+2][z]) {
					g->Tiles[i][z] = 0;
					g->Tiles[i+1][z] = 0;
					g->Tiles[i+2][z] = 0;
					addline(g);
					return;
				}
				if(c == g->Tiles[i+1][z+1] && c == g->Tiles[i+2][z+2]) {
					g->Tiles[i][z] = 0;
					g->Tiles[i+1][z+1] = 0;
					g->Tiles[i+2][z+2] = 0;
					addline(g);
					return;
				}

				if(bounds(i-2,z-2) && c == g->Tiles[i-1][z-1] && c == g->Tiles[i-2][z-2]) {
					g->Tiles[i][z] = 0;
					g->Tiles[i-1][z-1] = 0;
					g->Tiles[i-2][z-2] = 0;
					addline(g);
					return ;
				}

				if(bounds(i-2,z) && c == g->Tiles[i-1][z+1] && g->Tiles[i-2][z+2] == c) {

					g->Tiles[i][z] = 0;
					g->Tiles[i-1][z+1] = 0;
					g->Tiles[i-2][z+2] = 0;
					addline(g);
					return;
				}

				if(bounds(i,z-2) && c == g->Tiles[i+1][z-1] == c && g->Tiles[i+2][z-2] == c) {
					g->Tiles[i][z] = 0;
					g->Tiles[i+1][z-1] = 0;
					g->Tiles[i+2][z-2] = 0;
					addline(g);
					return;
				}
			}
		}
	}
	proc_blocks(g);
}


static void init_gblock(Block *b) {
	b->x = TILE_W/2;
	b->y = 0;
	srand((unsigned int)SDL_GetTicks());
	rand_block(b);
}

static void merge_block(mpGame *g) {
	g->Tiles[g->gblock.x][g->gblock.y] = g->gblock.color[0];
	g->Tiles[g->gblock.x][g->gblock.y+1] = g->gblock.color[1];
	g->Tiles[g->gblock.x][g->gblock.y+2] = g->gblock.color[2];
}

mpGame *winner = 0;
void game_over(mpGame *g) {
	if(g->player_num == 1) {
		winner = &game[1];
	}
	else winner = &game[0];
}


static void move_block(mpGame *g) {

	if(g->gblock.y < TILE_H-3) {
		if(g->Tiles[g->gblock.x][g->gblock.y+3] != 0) {
			if(g->gblock.y <= 1) {
				scr = ID_GAMEOVER;
				game_over(g);
			}
			else 
			merge_block(g);
			
			init_gblock(&g->gblock);
			
		}
		else
		g->gblock.y++;

	}
	else {
		merge_block(g);
		init_gblock(&g->gblock);
	}

}

void move_left(mpGame *g) {
	static int xcords = 0;

	if( (++xcords % 4 ) == 0) {

		if(g->gblock.x > 0 && g->gblock.y < TILE_H-3 && g->Tiles[g->gblock.x-1][g->gblock.y+2] == 0)
			g->gblock.x--;

	}
}

void move_right(mpGame *g) {
	
	static int xcords = 0;

	if( (++xcords % 4 ) == 0) {
		if(g->gblock.x < TILE_W-1 && g->gblock.y < TILE_H-3 && g->Tiles[g->gblock.x+1][g->gblock.y+2] == 0) g->gblock.x++;

	}
}

static void shift_blocks(Block *b, int pos) {

	Uint32 c[4];
	c[0] = b->color[0];
	c[1] = b->color[1];
	c[2] = b->color[2];
	b->color[0] = c[2];
	b->color[1] = c[0];
	b->color[2] = c[1];

}

static void check_input(mpGame *g) {
	int b = SDL_JoystickGetHat(g->stick, 0);
	if( b & SDL_HAT_LEFT ) {
		move_left(g);
	}
	if(b & SDL_HAT_RIGHT ) {
		move_right(g);
	}
	if(b & SDL_HAT_DOWN) {
	   static int w = 0;
	   if((++w % 4) == 0) 
		   move_block(g);
	}
	if(b & SDL_HAT_UP) {
	  static int w = 0;
	  if((++w % 8) == 0) 
		  shift_blocks(&g->gblock, 0);

	}

}

static void game_logic() {
	check_input(&game[0]);
	check_input(&game[1]);
	proccess_move_down(&game[0]);
	proccess_move_down(&game[1]);
}




Uint32 PlayerCall(Uint32 interval) {
	move_block(&game[0]);
	move_block(&game[1]);
	return interval;
}

void start_game() {
	SDL_SetTimer( 1000, PlayerCall );
}


static void in_render() {

	
	void *buf2 = lock(logo, logo->format->BitsPerPixel);
	void *buf = lock(start, start->format->BitsPerPixel);
	void *buf3 = lock(front, front->format->BitsPerPixel);
	int i,z;
	static float alpha = 0.0f;

	for(i = 0; i < front->w; i++) {
		for(z = 0; z < front->h; z++) {
			SDL_Color col1, col2;
			Uint32 color = 0;

			getpixel(logo, i, z, logo->format->BitsPerPixel, logo->pitch, &col2);
			getpixel(start, i, z, start->format->BitsPerPixel, start->pitch, &col1);
			color = SDL_MapRGB(front->format, ((Uint8)(alpha * col1.r) + (1-alpha) * col2.r), (Uint8)(alpha * col1.g) + (1-alpha) * col2.g , (Uint8) (alpha * col1.b) + (1-alpha) * col2.b);
			setpixel(buf3, i , z, color, front->format->BitsPerPixel, front->pitch);
		}
	}

	alpha += 0.1f;

	if(alpha > 3.0) {
		//start_game();
		scr = ID_START;

	}

	unlock(front);
	unlock(start);
	unlock(logo);

}

static void st_render() {
	render_start();
}


static void render_grid(mpGame *game, int x, int y) {

	int i,z;

	int off_x = x, off_y = y;


	for(i = 0; i < TILE_W; i++) {
		for(z = 0; z < TILE_H; z++) {
			SDL_Rect rc = { off_x, off_y, 14, 14 };
			// check tiles
			if(game->Tiles[i][z] != 0)
			//SDL_FillRect(front, &rc, game->Tiles[i][z]);
			SDL_BlitSurface(gfx[game->Tiles[i][z]], 0, front, &rc);
			if(game->gblock.x == i && game->gblock.y == z) {
				SDL_Rect rc2 = { off_x, off_y+16, 14, 14 };
				SDL_Rect rc3 = { off_x, off_y+32, 14, 14 };

				//SDL_FillRect(front, &rc, color_map[game->gblock.color[0]]);
				//SDL_FillRect(front, &rc2, color_map[game->gblock.color[1]]);
				//SDL_FillRect(front, &rc3, color_map[game->gblock.color[2]]);
				SDL_BlitSurface(gfx[game->gblock.color[0]], 0, front, &rc);
				SDL_BlitSurface(gfx[game->gblock.color[1]], 0, front, &rc2);
				SDL_BlitSurface(gfx[game->gblock.color[2]], 0, front, &rc3);
			}

			off_y += 16;
		}
		off_x += 16;
		off_y = y;
	}
}


static void g_render() {

	static char sbuf[256];
//	SDL_FillRect(front, &game[0].cords, SDL_MapRGB(front->format, 255, 255, 255));
//	SDL_FillRect(front, &game[1].cords, SDL_MapRGB(front->format, 255, 0, 0));
	SDL_BlitSurface( gbg, 0, front, 0);

	{
		SDL_Rect rc = { 20, 50, 640/2-40, 480-50 };
		SDL_Rect rc2 = { 640/2+20, 50, 640/2-40, 480-50 };
		SDL_FillRect(front, &rc, 0x0);
		SDL_FillRect(front, &rc2, 0x0);
		render_grid(&game[0], rc.x+5, rc.y+3);
		render_grid(&game[1], rc2.x+5, rc2.y+3);
		sprintf(sbuf, "P1 Score: %d Lines: %d", game[0].score, game[0].lines);
		SDL_PrintText(front, font, 25, 65, SDL_MapRGB(front->format, 255, 0, 0), sbuf);
		sprintf(sbuf, "P2 Score: %d Lines: %d", game[1].score, game[1].lines);
		SDL_PrintText(front, font, 640/2+25, 65, SDL_MapRGB(front->format, 255, 255, 255), sbuf);
	}
	game_logic();

}

static void go_render() {

	SDL_Rect rc = { 25, 100, 640-50, 480-200 };
	SDL_BlitSurface( gbg, 0, front, 0);
	SDL_FillRect( front, &rc, 0);
	{
		static char sbuf[256];

		sprintf(sbuf, "Player %d Wins with Score of %d!!", winner->player_num,  winner->score );
		SDL_PrintText(front, font, rc.x+25, rc.y+25, SDL_MapRGB(front->format, 255, 255, 255), sbuf);
		sprintf(sbuf, "Player %d Press Button 1 to Continue", winner->player_num);
	}
	{

		int i;
		for( i = 0; i < 12; i++) {

			if(SDL_JoystickGetButton(winner->stick, i)) {
				scr = ID_START;
				init_game();
			}
		}

	}
}


void render(int screen) {

	switch(screen) {
		case ID_INTRO:
			in_render();
			break;
		case ID_START:
			st_render();
			break;
		case ID_GAME:
			g_render();
			break;
		case ID_GAMEOVER:
			go_render();
			break;
	}
}

static void SDL_SetRect(SDL_Rect *rc, int x, int y, int w, int h) {
	rc->x = x, rc->y = y, rc->w = w, rc->h = h;
}

static void rand_block(Block *b) {


	do {

		b->color[0] = 1+(rand()%7);
		b->color[1] = 1+(rand()%7);
		b->color[2] = 1+(rand()%7);

	} while ( b->color[0] == b->color[1] && b->color[0] == b->color[2] );

}



void init_game() {
	memset(game, 0, sizeof(game));
	SDL_SetRect(&game[0].cords, 0, 0, 640/2, 480);
	SDL_SetRect(&game[1].cords, 640/2, 0, 640/2, 480);
	game[0].stick = stick[0];
	game[1].stick = stick[1];
	game[0].player_num = 1;
	game[1].player_num = 2;
	init_gblock(&game[0].gblock);
	init_gblock(&game[1].gblock);
	color_map[0] = SDL_MapRGB(front->format, 255, 255, 255);
	color_map[1] = SDL_MapRGB(front->format, 0, 255, 0);
	color_map[2] = SDL_MapRGB(front->format, 255, 0, 0);
	color_map[3] = SDL_MapRGB(front->format, 0, 0, 255);
	color_map[4] = SDL_MapRGB(front->format, 0xFF, 0x1A, rand()%255);
	color_map[5] = SDL_MapRGB(front->format, 0xFF, 0xFF, 0);
	color_map[6] = SDL_MapRGB(front->format, 0, 0xFF, 0xFF);
	color_map[7] = SDL_MapRGB(front->format, 0xFF, 0, 0xFF);

}

