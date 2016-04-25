#include "cross_gta.h"
#include "knight.h"
#include <pspdisplay.h>

#include "utils.c"
#include "cross_gta.c"

void init();
void draw();
void logic();
void drawboard();
void drawknight();
void clearboard();
void nextmove();

void render() {
	int i,z;
	draw();
	//draw_text(font_array, font_w, font_h, 0,0, rand()%0xFFFFFFFFL, "KT");
	//draw_text(font_array, font_w, font_h, 0,30,map_rgb(0,0,255),"by jared");
	
}

void joy_button(int button) {
	switch(button) {
		case 0:
			nextmove();
			break;
		case 1:
			init();
			break;
	}
}

/**** from knightstour.c **********/


struct Position
{
	int row,col;
};

struct Position pos;

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


	



void init() {
	pos.row = 1;
	pos.col = 6;
	clearboard();
}

void draw() {
	drawboard();
	drawknight();
}

void logic() {

}

void drawboard() {

	
	int dx,dy;
	unsigned long curcolor;
	int ion = 1;
	startx = 100;
	starty = 0;
	counter = 0;
	dx = startx;
	dy = starty;
	
	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
			if(ion == 1)
			{
				curcolor = 0xFFFFFFFFL;
			}
			else
			{
				curcolor = 0xFF;
			}
			ion = !ion;

			if(board[i][z] == 0)
			{

				fill_rect(dx,dy,dx+30,dy+30, curcolor);

			}

			dx += 35;
			counter++;
			if(counter >= 8)
			{
				counter = 0;
				dy += 35;
				dx = startx;
				ion = !ion;
			}

		}
	}

}

void drawknight() {
	
	static int dx,dy;
	static int ion = 1;
	dx = startx;
	dy = starty;
	
	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
		
			if(pos.row == i && pos.col == z)
			{
				
				draw_bitmap(data_bits, dx-5, dy, data_w, data_h, data_w, data_h,  0x00FFFFFFL);
				return;
			}

			dx += 35;
			counter++;
			if(counter >= 8)
			{
				counter = 0;
				dy += 35;
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

/**** end from knightstour.c *****/

void Main(void) {
	init_app();
	init();
	loop(render,joy_button);
	clean_app();
}