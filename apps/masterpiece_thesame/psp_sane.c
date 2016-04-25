#include<SDL.h>
#include<SDL_mxf.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define GRID_X 15
#define GRID_Y 16
#define NULL_BLOCK 0x3F
// global variables

SDL_Surface *front = 0, *bg = 0;
struct SDL_Font *font = 0;

int score = 0;
unsigned char grid[GRID_X+2][GRID_Y+2];
static char *block_names[] = { "block_clear.bmp", "block_dblue.bmp", "block_gray.bmp", "block_green.bmp","block_ltblue.bmp",
"block_orange.bmp", "block_pink.bmp", "block_red.bmp", "block_yellow.bmp", 0 };
SDL_Surface *block_surf[9];

// function prototypes
void render();
void init();
void free_prog();
void draw_grid();
void fill_grid();
void move(unsigned char direction);
void do_action();
void proc_blocks();

// structures
struct player_pos { unsigned int x,y; } pos;


int main(int argc, char **argv) {
	
	static SDL_Event e;
	SDL_Joystick *stick = 0;
	int active = 1;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;

	front = SDL_SetVideoMode(480,272,0,0);
	SDL_WM_SetCaption("MasterPiece *Same Edition* - LostJared", 0);
	if(!front) return -1;

	stick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);

	init();
	font = (struct SDL_Font*)SDL_InitFont("system.mxf");

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
				move(e.key.keysym.sym);
			}
			break;
			case SDL_JOYBUTTONDOWN:
				move((unsigned char)e.jbutton.button);
				break;
			break;
			}
		}
		SDL_UpdateRect(front, 0, 0, 480, 272);
	
	}

	free_prog();
	SDL_FreeFont(font);
	SDL_FreeSurface(front);
	SDL_JoystickClose(stick);
	SDL_Quit();
	return 0;
} 

void init() {

	unsigned int i;

	memset(&pos, 0, sizeof(pos));
	memset(grid, 0, sizeof(grid));
	fill_grid();
	for(i = 0; i < 9; i++) {
		block_surf[i] = SDL_LoadBMP(block_names[i]);
		if(!block_surf[i])
			fprintf(stderr, "Error loading surface %s\n", block_names[i]);
	}
	bg = SDL_LoadBMP("bg.bmp");


}

void free_prog() {
	unsigned int i;
	for(i = 0; i < 9; i++) 
		SDL_FreeSurface(block_surf[i]);

	SDL_FreeSurface(bg);

}

void fill_grid() {
	unsigned int i,z;
	srand((unsigned int) time(0));
	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y; z++) {
			grid[i][z] = rand()%9;
		}
	}

}
void render() {
	static char buf[256];
	SDL_BlitSurface(bg, 0, front, 0);
	draw_grid();
	sprintf(buf, "MasterPiece *Same Edition*  Score %d ", score);
	SDL_PrintText(front, font, 10, 0, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), buf);

}

 
void draw_grid() {
	unsigned int i,z,offset = 16;
	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y; z++) {

			SDL_Rect rc = { i*32, z*16+offset, i*32+32, z*16+16+offset };
			if(grid[i][z] != NULL_BLOCK) {
				SDL_BlitSurface(block_surf[grid[i][z]],0, front, &rc);
			}

			if(pos.x == i && pos.y == z) {
				SDL_FillRect(front, &rc, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255));
			}
		}
	}

}

void move(unsigned char direction) {
	switch(direction) {
	case 'w': // Up
	case 8:
		if(pos.y > 0) pos.y--;
		break;
	case 's': // Down
	case 6:
	
		if(pos.y < GRID_Y) pos.y++;
		break;
	case 'a': // Left
	case 7:
		if(pos.x > 0) pos.x--;
		break;
	case 'd':// Right
	case 9:
		if(pos.x < GRID_X) pos.x++;
		break;
	case 'z':// Triangle
	case 0:
	proc_blocks();
	break;
	case 'x':// Cross
	case 2:
	do_action();
	break;
	case 'n':// Start
	case 11:
		pos.x = pos.y = score = 0;
		fill_grid();
	break;
	}
	
}

void do_action() {

	unsigned char cur_block = grid[pos.x][pos.y];
	unsigned int cpos = 0,score_cnt = 0;
	for(cpos = pos.x; cpos < GRID_X; cpos++) {
		if(grid[cpos][pos.y] == cur_block)
			grid[cpos][pos.y] = NULL_BLOCK, score += score_cnt++;
		else
		break;
	}
	for(cpos = pos.x-1; cpos > 0; cpos--)
		if(grid[cpos][pos.y] == cur_block)
			grid[cpos][pos.y] = NULL_BLOCK, score += score_cnt++;
		else
		break;
		
	for(cpos = pos.y+1; cpos < GRID_Y; cpos++) 
		if(grid[pos.x][cpos] == cur_block)
			grid[pos.x][cpos] = NULL_BLOCK, score += score_cnt++;
		else
		break;
		
	for(cpos = pos.y-1; cpos > 0; cpos--)
		if(grid[pos.x][cpos] == cur_block)
			grid[pos.x][cpos] = NULL_BLOCK, score += score_cnt++;
		else
		break;


}

void proc_blocks() {
	unsigned int i,z;
	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y; z++) {
			unsigned char cpos = grid[i][z];
			if(cpos != NULL_BLOCK && grid[i][z+1] == NULL_BLOCK) {
				grid[i][z+1] = cpos;
				grid[i][z] = NULL_BLOCK;
				
			}
		}
	}
}
