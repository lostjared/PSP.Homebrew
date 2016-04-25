/* MasterPiece translated to C by Jared */


#ifndef __MPC__H_
#define __MPC__H_
#include "cross_gta.h"
#ifdef FOR_PSP
#include "utils.c"
#include "cross_gta.c"

#endif

#include "block.h"

enum { D_DOWN = 1, D_UP = 2 };
enum { STARTX = 185 , STARTY = 95 };
enum { BLOCK_BLACK = 0, BLOCK_YELLOW, BLOCK_ORANGE, BLOCK_LTBLUE, BLOCK_DBLUE, BLOCK_PURPLE, BLOCK_PINK,BLOCK_GRAY,BLOCK_RED,BLOCK_GREEN,BLOCK_CLEAR, BLOCK_FADE };

// the game object
const int BR  = 5;
void proccess_move_down();

struct Color {
	int c1,c2,c3;
};

struct GameBlock {
	struct Color col;
	int x,y;
};

static int Tiles[8+25][17+25] = { 0 };
static struct GameBlock gblock,nblock;
static int score = 0, lines = 0;

void block_randcolor(struct GameBlock *c) {
	do {

		c->col.c1 = 1+(rand()%8);
		c->col.c2 = 1+(rand()%8);
		c->col.c3 = 1+(rand()%8);

	} while ( c->col.c1 == c->col.c2 && c->col.c1 == c->col.c3 );

}

void block_copy(struct GameBlock *in, struct GameBlock *out) {
	out->col.c1 = in->col.c1;
	out->col.c2 = in->col.c2;
	out->col.c3 = in->col.c3;
}

void shiftcolor(struct GameBlock *c, int dir)
{
	int ic1;
	int ic2;
	int ic3;
	ic1 = c->col.c1;
	ic2 = c->col.c2;
	ic3 = c->col.c3;

	if(dir)
	{
		c->col.c1 = ic3;
		c->col.c2 = ic1;
		c->col.c3 = ic2;
	}
	else
	{
		c->col.c1 = ic2;
		c->col.c2 = ic3;
		c->col.c3 = ic1;
	}
}

int rand_table[10];
// from Fanjita's Tetris
unsigned long colours[10] =
{
  0x00000000L,
  0x00FFFFFFL,
  0x00FF00FFL,
  0x000000FFL,
  0x00FF0000L,
  0x0000FF00L,
  0x0000FFFFL,
  0x00FFFF00L,
  0x00FFFF88L,
  0x00FF00FFL
};
// end from tetris

void init_matrix() {
	int i,z;
	int total = 0;

	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 17; z++)
			Tiles[i][z] = 0;
	}

	rand_table[1] = map_rgb(255,0,0);
	rand_table[2] = map_rgb(0,255,0);
	rand_table[3] = map_rgb(0,0,255);
	rand_table[4] = map_rgb(255,255,255);
	rand_table[5] = map_rgb(0,255,255);
	rand_table[6] = map_rgb(255,0,255);
	rand_table[7] = map_rgb(255,255,0);
	rand_table[8] = map_rgb(0x80,0x00,0x80); // ##800080
	rand_table[9] = map_rgb(rand()%0xBD,rand()%0x2A,rand()%0xFF);



	block_randcolor(&gblock);
	block_randcolor(&nblock);
	gblock.x = 3;
	gblock.y = 0;
	Tiles[16][0] = 0;
	Tiles[16][3] = 0;

	// check to see if its all good
}

void draw_bitmap_colored(unsigned long *raw_bits,  int x, int y, int w, int h, int orig_w, int orig_h, unsigned long ckey, unsigned long add_color) {
	int i,z;

	for(i = 0; i < w; i++)
		for(z = h; z > 0; z--) {
			int pos_x = i;
			int pos_y = z;
			set_pixel(i+x,z+y, raw_bits[pos_x+pos_y*w]+add_color);
		}

}

// color constants dont stand for the acutal colors of blocks
void draw_block(int x, int y, int type) {


	//draw_bitmap_colored(data_bits, x,y,data_w,data_h,data_w,data_h, 0xFFFFFF00L, colours[type]/2);
	fill_rect(x,y,data_w,data_h, rand_table[type]);
}



void draw_grid() {

	int offset_x = 100, offset_y = 0;
	int i,z;
	for(i = 0; i < 8; i++) {
		for(z = 0; z < 17; z++) {
			if(Tiles[i][z] != 0)
			draw_block(offset_x+i,offset_y+z, Tiles[i][z]);

			if(gblock.x == i && gblock.y == z) {
				draw_block(offset_x+i,offset_y+z, gblock.col.c1);
				draw_block(offset_x+i,offset_y+z+data_h, gblock.col.c2);
				draw_block(offset_x+i,offset_y+z+data_h*2,gblock.col.c3);

			}
			offset_y += data_h;
		}

		offset_y = 0;
		offset_x += data_w;
	}

}

void release_block() {

	block_copy(&nblock,&gblock);
	block_randcolor(&nblock);
	gblock.x = 3;
	gblock.y = 0;

}

void setblock() {

	if(gblock.y <= 3) {
		// game over
		init_matrix();
		return;
	}
	Tiles[gblock.x][gblock.y] = gblock.col.c1;
	Tiles[gblock.x][gblock.y+1] = gblock.col.c2;
	Tiles[gblock.x][gblock.y+2] = gblock.col.c3;
	release_block();
}

void proc_move() {
	static int wait = 0; int platform_wait = 30;
	
	proccess_move_down();

	if( gblock.y +  3 >= 16 )
	{
			setblock();
			return;
	}
	
	if( Tiles[ gblock.x ][ gblock.y + 3] != 0 )
	{
		setblock();
		return;
	}


#ifndef FOR_PSP
	platform_wait = 50;
#endif
	// wait 30 frames before movement
	if(++wait > platform_wait) {
		wait = 0;
		if( gblock.y < 16-3 )
		{
			gblock.y++;
		}
	}

}



void move_left() {
	if( Tiles [ gblock.x-1 ] [ gblock.y ] == 0 && Tiles [ gblock.x-1 ] [ gblock.y + 1 ] == 0 && Tiles [gblock.x-1 ] [ gblock.y  + 1  ] == 0 && Tiles [ gblock.x-1 ] [ gblock.y + 3 ] == 0)

	if(gblock.x > 0)
	{
		gblock.x--;
	}
}

void move_right() {

	if( Tiles [ gblock.x+1  ] [ gblock.y ] == 0 && Tiles [ gblock.x+1 ] [  gblock.y + 1 ] == 0 && Tiles [ gblock.x+1 ] [ gblock.y  + 1 ] == 0 && Tiles [ gblock.x+1 ] [ gblock.y + 3 ] == 0)

	if(gblock.x < 7)
		gblock.x++;
}



void proc_blocks() {
	int i,z;
	for(i = 0; i < 8; i++) {
		for(z = 0; z < 15; z++) {

			if(Tiles[i][z] != 0 && Tiles[i][z+1] == 0) {
				Tiles[i][z+1] = Tiles[i][z];
				Tiles[i][z] = 0;
			}
		}
	}
}



void addline() {
	score += 5;
	lines++;
}

int bounds(int x, int y) {
	if(x >= 0 && y >= 0)
		return 1;
	return 0;
}

void proccess_move_down() {
	int i,z;

	for(i = 0; i < 8; i++) {
		for(z = 0; z < 17; z++) {
			int c = Tiles[i][z];
			if(c != 0) {
				if(c == Tiles[i][z+1] && c == Tiles[i][z+2]) {
					Tiles[i][z] = 0;
					Tiles[i][z+1] = 0;
					Tiles[i][z+2] = 0;
					addline();
					return;
				}

				if(c == Tiles[i+1][z] && c == Tiles[i+2][z]) {
					Tiles[i][z] = 0;
					Tiles[i+1][z] = 0;
					Tiles[i+2][z] = 0;
					addline();
					return;
				}
				if(c == Tiles[i+1][z+1] && c == Tiles[i+2][z+2]) {
					Tiles[i][z] = 0;
					Tiles[i+1][z+1] = 0;
					Tiles[i+2][z+2] = 0;
					addline();
					return;
				}

				if(bounds(i-2,z-2) && c == Tiles[i-1][z-1] && c == Tiles[i-2][z-2]) {
					Tiles[i][z] = 0;
					Tiles[i-1][z-1] = 0;
					Tiles[i-2][z-2] = 0;
					addline();
					return ;
				}

				if(bounds(i-2,z) && c == Tiles[i-1][z+1] && Tiles[i-2][z+2] == c) {

					Tiles[i][z] = 0;
					Tiles[i-1][z+1] = 0;
					Tiles[i-2][z+2] = 0;
					addline();
					return;
				}

				if(bounds(i,z-2) && c == Tiles[i+1][z-1] == c && Tiles[i+2][z-2] == c) {
					Tiles[i][z] = 0;
					Tiles[i+1][z-1] = 0;
					Tiles[i+2][z-2] = 0;
					addline();
					return;
				}
			}
		}
	}
	proc_blocks();
}

#endif

// after all its written in the stars - John Lennon

