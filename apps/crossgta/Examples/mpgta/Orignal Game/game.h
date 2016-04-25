
#include"theheader.h"
// From an another game I wrote, minor changes


enum { D_DOWN = 1, D_UP = 2 };
enum { STARTX = 185 , STARTY = 95 };
enum { BLOCK_BLACK = 0, BLOCK_YELLOW, BLOCK_ORANGE, BLOCK_LTBLUE, BLOCK_DBLUE, BLOCK_PURPLE, BLOCK_PINK,BLOCK_GRAY,BLOCK_RED,BLOCK_GREEN,BLOCK_CLEAR, BLOCK_FADE };

// the game object
const int BR  = 5;
void getcords(int r, int c, int& rx, int& ry)
{
	int STARTPOSX = STARTX;
	int STARTPOSY = STARTY;
	int x = STARTPOSX,y = STARTPOSY;

	for(int i = 0; i < 17; i++)
	{
		for(int j = 0; j < 8; j++)
		{

			if(r == i && c == j)
			{
				rx = x;
				ry = y;
				return;
			}
			x = x + 32;
		}
		x = STARTPOSX;
		y = y + 16;
		// down lower
	}
	rx = -1;
	ry = -1;
}

// contains the game grid
// which is were the game play occours
class Game  {

public:

	bool paused;

	// games tile matrix
	class TileMatrix {

	public:

		struct GameData {

			unsigned long score;
			int lines;
			int speed;
			int lineamt;


			inline GameData()
			{
				newgame();
			}

			inline void newgame()
			{
				score = 0;
				lines = 0;
				speed = 20;
				lineamt;
			}

			inline void addline()
			{
				lines++;
				score += 6;
				lineamt++;

				if(lineamt >= linenum)
				{
					lineamt = 0;
					speed = speed - 4;
					if(speed < 4)
					{
						speed = 5;
					}
				}

				//				shandle.sounds[1].Play();

			}
		};

		struct GameBlock {


			struct Color {
				int c1,c2,c3;

				inline void randcolor()
				{
					c1 = rand()%10;
					c2 = rand()%10;
					c3 = rand()%10;
					if(c1 == 0) { c1++; }
					if(c2 == 0) { c2++; }
					if(c3 == 0) { c3++; }


					// were all the same
					if(c1 == c2 && c1 == c3)
					{
						randcolor();// try again
						return;
					}
				}

				inline void copycolor(Color* c)
				{
					c1 = c->c1;
					c2 = c->c2;
					c3 = c->c3;
				}

				// shift the colors up and down (true & false)
				inline void shiftcolor(bool dir)
				{
					int ic1;
					int ic2;
					int ic3;
					ic1 = c1;
					ic2 = c2;
					ic3 = c3;

					if(dir)
					{
						c1 = ic3;
						c2 = ic1;
						c3 = ic2;
					}
					else
					{
						c1 = ic2;
						c2 = ic3;
						c3 = ic1;
					}
				}

			};

			Color color;
			Color nextcolor;

			int x,y;

			inline GameBlock()
			{
				color.randcolor();
				nextcolor.randcolor();
			}

			inline void NextBlock()
			{
				color.copycolor(&nextcolor);
				nextcolor.randcolor();
				x = 3;
				y = 0;

			}

			inline void MoveDown()
			{
				if( y < 16 )
				{

					y++;

				}
			}

			inline void MoveLeft()
			{
				if(x > 0)
				{
					x--;
				}
			}

			inline void MoveRight()
			{
				if(x < 7)
				{
					x++;
				}
			}


		};

		GameData Game;
		GameBlock block;
		// breathing room
		int Tiles[17 + BR][8 + BR];

		inline void cleartiles()
		{


			for(int i = 0; i < 17; i++)
			{
				for(int j = 0; j < 8; j++)
				{
					if( i <= 16 && j <= 7)
						Tiles[i][j] = 0;
				}
			}

		}

		// initilize the matrix, for a new game
		inline void init_matrix()
		{
			cleartiles();
			Game.newgame();
			block.NextBlock();

		}

		inline void setblock()
		{
			if ( block.y <= 0 )
			{
					gameover();
					mxhwnd.setScreen(START);
				//mxhwnd.setScreen(HIGHSCORES);
			}

			Tiles[ block.y ] [ block.x ] = block.color.c1;
			Tiles[ block.y+1 ] [ block.x ] = block.color.c2;
			Tiles[ block.y+2 ] [ block.x ] = block.color.c3;
			block.NextBlock();

		}

		// constructor

		inline TileMatrix()
		{
			cleartiles();
		}

		// proccess the blocks, move them down (this occours, when a line is cleared )
		inline void ProccessBlocks()
		{
			for(int z = 0; z < 8; z++)
			{
				for(int i = 0; i < 16; i++)
				{
					if(Tiles[i][z] != 0 && Tiles[i+1][z] == 0)
					{
						Tiles[i+1][z] = Tiles[i][z];
						Tiles[i][z] = 0;
					}
				}
			}
		}


	};

	TileMatrix matrix;



	void load()
	{
		// lets load up are graphics
		grid_blocks[0].load(&mxhwnd,getPath("block_black.bmp"));
		grid_blocks[1].load(&mxhwnd,getPath("block_yellow.bmp"));
		grid_blocks[2].load(&mxhwnd,getPath("block_orange.bmp"));
		grid_blocks[3].load(&mxhwnd,getPath("block_ltblue.bmp"));
		grid_blocks[4].load(&mxhwnd,getPath("block_dblue.bmp"));
		grid_blocks[5].load(&mxhwnd,getPath("block_purple.bmp"));
		grid_blocks[6].load(&mxhwnd,getPath("block_pink.bmp"));
		grid_blocks[7].load(&mxhwnd,getPath("block_gray.bmp"));
		grid_blocks[8].load(&mxhwnd,getPath("block_red.bmp"));
		grid_blocks[9].load(&mxhwnd,getPath("block_green.bmp"));
		grid_blocks[10].load(&mxhwnd,getPath("block_clear.bmp"));
		gbg.load(&mxhwnd,getPath("gamebg.bmp"));
		matrix.init_matrix();
		paused = false;
	}


	void update()
	{ 
		draw();
		if(paused == true)
		{
			font.printText(20,20, "Game Paused press P To Continue.");
			return;
		}
		SDL_Delay(30);
		logic();
	}

	inline void draw()
	{
		gbg.display(0,0);
		drawmatrix();
		drawblock();
		char temp[255];
		sprintf(temp, "Score: %i", matrix.Game.score);
		font.printText(200,60,temp);
		sprintf(temp, "Tabs: %d", matrix.Game.lines);
		font.printText(310,60,temp);
	}

	inline void logic()
	{
		static int wait = 0;
		wait++;

		if(wait > matrix.Game.speed )
		{
			wait = 0;
			matrix.block.MoveDown();			
		}


		blockProc();

	}

	// disolve the block
	void draweffect(int q, int p)
	{
		int px, py;
		getcords(q,p,px,py);
		for(int v = 0; v < 255; v++)
			mxhwnd.setPixel(mxhwnd.pscr, px+rand()%grid_blocks[0].sptr->w, py+rand()%grid_blocks[0].sptr->h, 0x0);
		//paint.drawRect(px,py,grid_blocks[0].sptr->w, grid_blocks[0].sptr->h, SDL_MapRGB(mxhwnd.pscr->format,rand()%255,rand()%255,rand()%255));
		SDL_Delay(5);
	}

	// proccess the blocks
	inline void blockProc()
	{
		// are we at the bottom ?
		if( matrix.block.y + 2 >= 16 )
		{
			matrix.setblock();
			return;
		}
		// did I run into another block?
		if( matrix.Tiles[ matrix.block.y + 3][matrix.block.x] != 0 )
		{
			matrix.setblock();
			return;
		}

		// now check and see if they are any 3 in a row going across

		for(int i = 0; i < 17; i++)
		{
			for(int j = 0; j < 8-2; j++)
			{
				int cur_color;
				cur_color = matrix.Tiles[ i ][ j ];
				if(cur_color != BLOCK_BLACK) 
				{

					if( matrix.Tiles [i][j+1] == cur_color && matrix.Tiles[i][j+2] == cur_color )
					{
						matrix.Game.addline();
						matrix.Tiles[i][j] = 0;
						matrix.Tiles[i][j+1] = 0;
						matrix.Tiles[i][j+2] = 0;
						for(int pq = 0; pq < 25; pq++)
						{
							draweffect(i,j);
							draweffect(i,j+1);
							draweffect(i,j+2);
							SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
						}
						return;
					}

				}

			}
		}

		// now check and see if there are any 3 i a row going down
		for(int z = 0; z < 8; z++)
		{
			for(int q = 0; q < 17-2; q++)
			{
				int cur_color = matrix.Tiles[q][z];
				if( cur_color != BLOCK_BLACK )
				{

					if( matrix.Tiles[q+1][z] == cur_color && matrix.Tiles[q+2][z] == cur_color )
					{
						matrix.Tiles[q][z]  = 0;
						matrix.Tiles[q+1][z] = 0;
						matrix.Tiles[q+2][z] = 0;
						matrix.Game.addline();
						for(int pq = 0; pq < 25; pq++)
						{
							draweffect(q,z);
							draweffect(q+1,z);
							draweffect(q+2,z);
							SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
						}
						return;
					}
				}
			}
		}

		//now lets see if we can find any diagnoal
		for(int p = 0; p < 8; p++)
		{
			for(int w = 0; w < 17; w++)
			{
				int cur_color;
				cur_color = matrix.Tiles[w][p];

				if(cur_color != 0 && cur_color != BLOCK_FADE)// we got a block ;]
				{
					// left
					if( matrix.Tiles [w+1][p+1] == cur_color && matrix.Tiles[w+2][p+2] == cur_color)
					{
						matrix.Tiles[w][p] = 0;
						matrix.Tiles[w+1][p+1] = 0;
						matrix.Tiles[w+2][p+2] = 0;
						matrix.Game.addline();
						for(int pq = 0; pq < 25; pq++)
						{
							draweffect(w,p);
							draweffect(w+1,p+1);
							draweffect(w+2,p+2);
							SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
						}
					}
					if( w-2 >= 0 && p-2 >= 0)
					{

						if(matrix.Tiles [w-1][p-1] == cur_color && matrix.Tiles[w-2][p-2] == cur_color)
						{
							matrix.Tiles[w][p] = 0;
							matrix.Tiles[w-1][p-1] = 0;
							matrix.Tiles[w-2][p-2] = 0;
							matrix.Game.addline();
							for(int pq = 0; pq < 25; pq++)
							{
								draweffect(w,p);
								draweffect(w-1,p-1);
								draweffect(w-2,p-2);
								SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
							}
						}

					}

					if(w-2 >= 0)
					{

						if(matrix.Tiles[w-1][p+1] == cur_color && matrix.Tiles[w-2][p+2] == cur_color)
						{
							matrix.Tiles[w][p] = 0;
							matrix.Tiles[w-1][p+1] = 0;
							matrix.Tiles[w-2][p+2] = 0;
							matrix.Game.addline();
							for(int pq = 0; pq < 25; pq++)
							{
								draweffect(w,p);
								draweffect(w-1,p+1);
								draweffect(w-2,p+2);
								SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
							}
						}

					}

					if(p-2 >= 0)
					{

						if(matrix.Tiles[w+1][p-1] == cur_color && matrix.Tiles[w+2][p-2] == cur_color)
						{
							matrix.Tiles[w][p] = 0;
							matrix.Tiles[w+1][p-1] = 0;
							matrix.Tiles[w+2][p-2] = 0;
							matrix.Game.addline();
							for(int pq = 0; pq < 25; pq++)
							{
								draweffect(w,p);
								draweffect(w+1,p-1);
								draweffect(w+2,p-2);
								SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
							}
						}

					}
				}
			}


		}
		matrix.ProccessBlocks();

	}

	// draw the matrix
	inline void drawmatrix()
	{

		int STARTPOSX = STARTX;
		int STARTPOSY = STARTY;
		int x = STARTPOSX,y = STARTPOSY;
		static int c_counter = 1;

		for(int i = 0; i < 17; i++)
		{


			for(int j = 0; j < 8; j++)
			{
				if(matrix.Tiles[i][j] != BLOCK_FADE)
				{
					if(matrix.Tiles[i][j] != BLOCK_BLACK)
						grid_blocks[matrix.Tiles[i][j]].display(x,y);
					x = x + 32;
				}
			}
			x = STARTPOSX;
			y = y + 16;
			// down lower
		}


		// draw the next block
		int bx = 510; int by = 200;


		grid_blocks[matrix.block.nextcolor.c1].display(bx,by);
		grid_blocks[matrix.block.nextcolor.c2].display(bx,by+16);
		grid_blocks[matrix.block.nextcolor.c3].display(bx,by+32);




	}
	// draw the blocks
	inline void drawblock()
	{
		int bx;
		int by;
		getcords(matrix.block.y,matrix.block.x,bx,by);
		grid_blocks[matrix.block.color.c1].display(bx,by);
		getcords(matrix.block.y+1,matrix.block.x,bx,by);
		grid_blocks[matrix.block.color.c2].display(bx,by);
		getcords(matrix.block.y+2,matrix.block.x,bx,by);
		grid_blocks[matrix.block.color.c3].display(bx,by);


	}
	// keypress
	inline void keypress(int wParam)
	{
		switch(wParam)
		{
		case 276:
			if( matrix.block.x >= 1)
			{

				if( matrix.Tiles [ matrix.block.y ] [ matrix.block.x-1 ] == 0 && matrix.Tiles [ matrix.block.y + 1 ] [ matrix.block.x-1 ] == 0 && matrix.Tiles [ matrix.block.y  + 1 ] [ matrix.block.x-1 ] == 0 && matrix.Tiles [ matrix.block.y + 3] [ matrix.block.x-1 ] == 0)
				{

					//grid.HandleInput(wParam);
					matrix.block.MoveLeft();

				}

			}
			break;
		case 275:
			if( matrix.block.x < 7)
			{

				if( matrix.Tiles [ matrix.block.y ] [ matrix.block.x+1 ] == 0 && matrix.Tiles [ matrix.block.y + 1 ] [ matrix.block.x+1 ] == 0 && matrix.Tiles [ matrix.block.y  + 1 ] [ matrix.block.x+1 ] == 0 && matrix.Tiles [ matrix.block.y + 3] [ matrix.block.x+1 ] == 0)
				{

					//grid.HandleInput(wParam);
					matrix.block.MoveRight();

				}

			}
			break;
		case 274:
			//	grid.HandleInput(wParam);
			if( matrix.Tiles [ matrix.block.y + 3 ][ matrix.block.x ] == 0 && matrix.block.y + 3 < 15 )
			{

				if(matrix.Tiles[ matrix.block.y + 4 ][ matrix.block.x ] == 0)
				{

					matrix.block.MoveDown();

				}

			}
			break;
		case 'A':
		case 'a':
			matrix.block.color.shiftcolor(true);
			break;
		case 'S':
		case 's':
			matrix.block.color.shiftcolor(false);
			break;
		}

	}

	void free()
	{
		for(int q = 0; q <= 10; q++)
			grid_blocks[q].~mxSprite();

		gbg.~mxSprite();
	}

private:

	mxSprite grid_blocks[11];
	mxSprite gbg;



};