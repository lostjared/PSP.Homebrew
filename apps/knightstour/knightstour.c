#include<SDL.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<SDL_mxf.h>


struct Position
{
	int row,col;
};

struct Position pos;
SDL_Surface *gknight = 0, *front = 0;
SDL_Joystick *joy = 0;
struct SDL_Font *font = 0;

int moves = 0,
startx = 50,
starty = 50,
i,z,counter,
board[8][8],
htable[8][8] = {
	{2,3,4,4,4,4,3,2},
	{3,4,6,6,6,6,4,3},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{3,4,6,6,6,6,4,3},
	{2,3,4,4,4,4,3,2}
};

int horizontal[8] = { 2,1,-1,-2,-2,-1,1,2 };
int vertical[8] = { -1,-2,-2,-1,1,2,2,1 };

void init();
void draw();
void logic();
void drawboard();
void drawknight();
void clearboard();
void nextmove();
	


extern int SDL_main(int argc, char **argv) {

	SDL_Event e;
	int active = 1;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;

	front = SDL_SetVideoMode(640,480,0,0);
	if(!front)
		return -1;

	init();
	while(active == 1) {

		SDL_FillRect(front, 0, 0);
		draw();


		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
				case SDL_KEYDOWN:
					{
						if(e.key.keysym.sym == SDLK_SPACE)
						nextmove();
						else if(e.key.keysym.sym == SDLK_RETURN)
						{
							clearboard();
							pos.row = 1;
							pos.col = 6;
							moves = 0;


						}
					}
					break;
				case SDL_JOYBUTTONDOWN:
					{
						if(e.jbutton.button == 0)
							nextmove();
						else if(e.jbutton.button == 1) {
							clearboard();
							pos.row = 1;
							pos.col = 6;
							moves = 0;
						}
					}
					break;
			}
		}

		SDL_UpdateRect(front, 0,0,640,480);

	}

	SDL_JoystickClose(joy);
	SDL_FreeSurface(gknight);
	
	SDL_FreeFont(font);
	SDL_Quit();
	return 0;
}

void init() {
	gknight = SDL_LoadBMP("knight.bmp");
	srand((unsigned int)time(0));
	pos.row = 1;
	pos.col = 6;
	clearboard();
	joy = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
	font = SDL_InitFont("arial.mxf");
}

void draw() {
	char buf[100];
	drawboard();
	drawknight();
	sprintf(buf,"KnightsTour for PSP - Total Moves: %d", moves);
	SDL_PrintText(front, font, 10,10, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), buf);
}

void logic() {

}

void drawboard() {

	
	int dx,dy;
	Uint32 curcolor;
	int ion = 1;
	startx = 100;
	starty = 30;
	counter = 0;
	dx = startx;
	dy = starty;
	
	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
			if(ion == 1)
			{
				curcolor = SDL_MapRGB(front->format, 255,255,255);
			}
			else
			{
				curcolor = SDL_MapRGB(front->format, 255,0,0);
			}
			ion = !ion;

			if(board[i][z] == 0)
			{

				SDL_Rect rc = {dx,dy,50,50};
				SDL_FillRect(front, &rc, curcolor);

			}

			dx += 55;
			counter++;
			if(counter >= 8)
			{
				counter = 0;
				dy += 55;
				dx = startx;
				ion = !ion;
			}

		}
	}

}

void drawknight() {
	static int dx,dy;
	static Uint32 curcolor;
	static int ion = 1;
	dx = startx;
	dy = starty;
	
	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
		
			if(pos.row == i && pos.col == z)
			{
				
				SDL_Rect rc2 = { dx,dy,dx+32,dy+32 };
				
				SDL_SetColorKey(gknight, SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255,255,255));
				SDL_BlitSurface(gknight, 0, front, &rc2);
				return;
			}

			dx += 55;
			counter++;
			if(counter >= 8)
			{
				counter = 0;
				dy += 55;
				dx = startx;
				ion = !ion;
			}

		}
	}
}

void clearboard() {

	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
			board[i][z] = 0;
		}
	}
}

void nextmove() {
	int smallest = 100;
	int choice = -1;

	for(i = 0; i < 8; i++)
	{
		int row,col;
		row = pos.row;
		col = pos.col;
		row += horizontal[i];
		col += vertical[i];
		if(row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == 0)
		{
			if(htable[row][col] < smallest && htable[row][col] != 0)
			{
				smallest = htable[row][col];
				choice = i;
			}
		}
	}

	if(choice != -1)
	{
		board[pos.row][pos.col] = 1;
		pos.row += horizontal[choice];
		pos.col += vertical[choice];
		moves++;
		if(moves == 63) 
		{
			moves++;
			board[pos.row][pos.col] = 1;
		}
	}
}