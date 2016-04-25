#ifndef __PUZZLE__H_
#define __PUZZLE__H_

//#define _MXBOX_H_
#include<SDL.h>
//#include<SDL_ttf.h>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstdarg>

enum screen_type { ID_INTRO, ID_GAME, ID_GAMEOVER };


extern void *lock(SDL_Surface *surf, Uint8 &type);
extern void unlock(SDL_Surface *surf);
inline void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 &type, Uint16 &pitch);
inline Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 &type, Uint16 &pitch);
extern void setscreen(screen_type t);

static char *imgs[] = { "block_red.bmp","block_clear.bmp", "block_dblue.bmp", 0 };


class Joystick {
public:
	Joystick(int num) {
		num_joy = SDL_NumJoysticks();
		OpenJoy(num);

	}
	~Joystick() {
		SDL_JoystickClose(joy);
	}

	void OpenJoy(int num) {
		joy = SDL_JoystickOpen(num);
		buttons = SDL_JoystickNumButtons(joy);
		SDL_JoystickEventState(SDL_ENABLE);
	}

	bool PollButton(int button) {

		if(SDL_JoystickGetButton(joy,button)) 
			return true;
		return false;

	}

	bool PollHat(int direction) {
		if(SDL_JoystickGetHat(joy,direction))
			return true;
		return false;
	}

	void Poll(SDL_Event &e) {
		if(e.type == SDL_JOYAXISMOTION) {
			if(e.jaxis.axis < 2)
			{
				axis[e.jaxis.axis] = e.jaxis.value >> 8;
			}
		}
	}

	SDL_Joystick *Get() { return joy; }

protected:
	int num_joy;
	SDL_Joystick *joy;
	int buttons;
public:
	int axis[2];

};

static const unsigned int block_count_x = 8, block_count_y = 12;

class PuzzleBox {
public:

	SDL_Surface *blocks_[3];
	//TTF_Font *font;
	int score;
	

	class Block {
	public:
		unsigned int x,y,cx,cy;
		int color;
		bool active;

		Block() { x = 0; y = 0; color = 0; active = false; srand(static_cast<unsigned int>(time(0))); }
		void clr() { color = 0; active = false; }
		~Block() {
		
		}

		void setpos(int x, int y) { this->x = x , this->y = y; }

		void CopyFrom(SDL_Surface *front, SDL_Surface *surf) {
			SDL_Rect src = { x,y, x+surf->w, y+surf->h }, pnt = { 0,0,surf->w,surf->h };
			SDL_BlitSurface(surf, &pnt, front, &src);
		}

	};

	SDL_Surface *block;
	Block blocks[3];


	PuzzleBox(SDL_Surface *front, const char *str, int grid_offset) {
		this->front = front;
		this->grid_offset = grid_offset;
		block = SDL_LoadBMP(str);
		if(block == 0) 
			return;

		for(unsigned int i = 0; i < 3; i++)
			blocks_[i] = SDL_LoadBMP(imgs[i]);
			
		
		init_blocks();

		SDL_Rect src = {0,0,480,272};
		SDL_BlitSurface(block, &src,  front, &src);
		SDL_UpdateRect(front, 0,0,480,272);
		color_dir = 0;


		//TTF_Init();

	//	font = TTF_OpenFont("fonts\\a.ttf", 24);
	//	if(font == 0) {
	//		std::cout << "Error couldnt open font \n";
	//	}

	}

	void init_blocks() {
		for(unsigned int i = 0; i < block_count_x; i++)
			for(unsigned int z = 0; z < block_count_y; z++)
			{
				grid[i][z].color = 0;
				grid[i][z].cx = i;
				grid[i][z].cy = z;
				grid[i][z].x = grid_offset+i*blocks_[0]->w;
				grid[i][z].y = grid_offset+z*blocks_[0]->h;
				grid[i][z].active = false;
			}
			next_block();

		score = 0;

	}

	void printtext(int x, int y, char *src, SDL_Color &col) {

		/*SDL_Surface *surf = TTF_RenderText_Solid(font, src, col);
		SDL_Rect rc = { x,y, this->front->w, this->front->w };
		SDL_BlitSurface(surf,0,this->front,&rc);
		SDL_FreeSurface(surf);*/

	}

	void next_block() {
			blocks[0].cx = 6;
			blocks[0].cy = 0;
			blocks[1].cx = 6;
			blocks[1].cy = 1;
			blocks[2].cx = 6;
			blocks[2].cy = 2;

			do {

			blocks[0].color = rand()%3;
			blocks[1].color = rand()%3;
			blocks[2].color = rand()%3;

			} while ( blocks[0].color == blocks[1].color && blocks[0].color == blocks[2].color ) ;

			blocks[0].active = true;
			blocks[1].active = true;
			blocks[2].active = true;
	}

	~PuzzleBox() {

		SDL_FreeSurface(block);
		for(unsigned int i = 0; i < 3; i++)
			SDL_FreeSurface(blocks_[i]);


	}

	

	Block grid[block_count_x+1][block_count_y+1];
	int grid_offset;

	void draw_grid() {
		
		for(unsigned int i = 0; i < block_count_x; i++)
			for(unsigned int z = 0; z <= block_count_y; z++) {
				if(grid[i][z].active)
					grid[i][z].CopyFrom(this->front, blocks_[grid[i][z].color]);
			}

			for(unsigned int i = 0; i < 3; i++)
			draw_block(blocks[i]);
	}

	
	void proc_blocks() {

		unsigned int i = 0, z = 0;
		for(i = 0; i < block_count_x; i++)
		{
			for(z = 0; z  < block_count_y; z++) {
				int cur_color = grid[i][z].color;
				if(bounds(i+2,z) && grid[i][z].active == true) {
					if((cur_color == grid[i+1][z].color) && grid[i+1][z].active == true && cur_color == grid[i+2][z].color && grid[i+2][z].active == true) {
						grid[i][z].clr();
						grid[i+1][z].clr();
						grid[i+2][z].clr();
						score++;
					}
				}

				if(bounds(i,z+2) && grid[i][z].active == true) {
					if(cur_color == grid[i][z+1].color && grid[i][z+1].active && grid[i][z+2].color == cur_color && grid[i][z+2].active) {
						grid[i][z].clr();
						grid[i][z+1].clr();
						grid[i][z+2].clr();
						score++;
					}
				}
			}
		}



		for(i = 0; i < block_count_x; i++) {
			for(z = 0; z < block_count_y; z++) {
				int cur_color;
				cur_color = grid[i][z].color;
				if(grid[i][z].active) {
					if(bounds(i+2,z+2) && grid[i+1][z+1].color == cur_color && grid[i+1][z+1].active && grid[i+2][z+2].color == cur_color && grid[i+2][z+2].active) {

						grid[i][z].clr();
						grid[i+1][z+1].clr();
						grid[i+2][z+2].clr();
						score++;
					}

					if(bounds(i-2,z-2) && grid[i-1][z-1].color == cur_color && grid[i-1][z-1].active  && grid[i-2][z-2].color == cur_color && grid[i-2][z-2].active) {
						grid[i][z].clr();
						grid[i-1][z-1].clr();
						grid[i-2][z-2].clr();
						score++;
					}

					if(bounds(i-2,z+2) && grid[i-1][z+1].color == cur_color && grid[i-1][z+1].active  && grid[i-2][z+2].color == cur_color && grid[i-2][z+2].active) {
						grid[i][z].clr();
						grid[i-1][z+1].clr();
						grid[i-2][z+2].clr();
						score++;
					}

					if(bounds(i+2,z-2) && grid[i+1][z-1].color == cur_color && grid[i+1][z-1].active  && grid[i+2][z-2].color == cur_color && grid[i+2][z-2].active) {
						grid[i][z].clr();
						grid[i+1][z-1].clr();
						grid[i+2][z-2].clr();
						score++;
					}

				}
			}

		}

	}

	void move_blocks_dir() {
		static int dir = 0;
		static int dcount = 0;

		switch(dir) {
			case 0: {
				for(unsigned int i = 0; i < block_count_x; i++)
					for(unsigned int z = 0; z < block_count_y; z++)
					{
						if(bounds(i,z-1) && grid[i][z].active == true && grid[i][z-1].active == false) {
							copy_block(grid[i][z], grid[i][z-1]);
							dcount++;
							if(dcount > 5)
							{
								dcount = 0;
								dir = 1;
							}
						}
					}
			}
			break;
			case 1:
			{
				for(unsigned int i = 0; i < block_count_x; i++)
					for(unsigned int z = 0; z < block_count_y; z++)
					{
						if(bounds(i,z+1) && grid[i][z].active == true && grid[i][z+1].active == false) {
							copy_block(grid[i][z], grid[i][z-1]);
							dcount++;
							if(dcount > 5)
							{
								dcount = 0;
								dir = 0;
							}
						}
					}
			}
			break;

		}
	}

	void check_for() {

	}

	void copy_block(Block &b1 , Block &b2 ) {
		b2.color = b1.color;
		b2.active = b1.active;
		b1.color = 0;
		b1.active = false;
	}


	bool bounds(unsigned int x, unsigned int y) {
		if(x >= 0 && x < block_count_x && y >= 0 && y < block_count_y)
			return true;
		return false;
	}
	void move_down() {


		if(bounds(blocks[2].cx,blocks[2].cy+1) && grid[blocks[2].cx][blocks[2].cy+1].active == false) {
			blocks[0].cy++;
			blocks[1].cy++;
			blocks[2].cy++;
		} else if(blocks[2].cy == 2) {
			setscreen(ID_GAMEOVER);
		}

	}

	void merge_blocks() {

		static unsigned int i;

		for(i = 0; i < 3; i++) {
			grid[blocks[i].cx][blocks[i].cy].color = blocks[i].color;
			grid[blocks[i].cx][blocks[i].cy].active = true;
		}
		next_block();
	}

	void move_left() {

		// see if it can move left
		unsigned int i;

		if(blocks[0].cx > 0 && grid[blocks[1].cx-1][blocks[1].cy].active == false && grid[blocks[2].cx-1][blocks[2].cy-1].active == false)

		for(i = 0; i < 3; i++)
		{
		move_left(blocks[i]);
		}
	}

	void move_left(Block &b) {
		b.cx--;
	}

	void move_right() {

		unsigned int i ;

		if(blocks[0].cx < block_count_x && grid[blocks[1].cx+1][blocks[1].cy].active == false && grid[blocks[2].cx+1][blocks[2].cy].active == false) 
		for(i = 0; i < 3; i++)
		move_right(blocks[i]);
	}

	void move_right(Block &b) {
			b.cx++;
	}

	void move_up(Block &b) {
		b.cy--;
	}

	void move_up() {
		if(blocks[0].cy > 1 && grid[blocks[0].cx][blocks[0].cy-1].active == false) {
			move_up(blocks[0]);
			move_up(blocks[1]);
			move_up(blocks[2]);
		}
	}

	void switch_color(Block *b) {
		int color1 = b[0].color;
		int color2 = b[1].color;
		int color3 = b[2].color;
		b[0].color = color3;
		b[1].color = color1;
		b[2].color = color2;

	}

	void draw_block(Block &b) {
		b.setpos(grid_offset+b.cx*blocks_[0]->w, grid_offset+b.cy*blocks_[0]->h);
		b.CopyFrom(this->front, blocks_[b.color]);
	}

	void render(void *buff, Uint8 &type, Uint16 &pitch) {
		this->buffer = buff;
		this->type = type;
		this->pitch = pitch;
		trip_it(0,0,block);
		draw_grid();
		proc_blocks();
	}

	void printtextf(int x, int y, SDL_Color col, char *src, ...) {
		va_list l;
		va_start(l,src);
		char buffer[2500];
		vsprintf(buffer,src,l);
		va_end(l);
		printtext(x,y,buffer,col);
	}

	void sp(int x, int y, Uint32 color) {
		setpixel(buffer,x,y,color,type,pitch);
	}

	Uint32 gp(int x, int y) {
		return (getpixel(front,x,y,type,pitch));
	}

	void trip_it(unsigned int x, unsigned int y, SDL_Surface *the_surf) {

		static Uint8 type;
		static int counter = 0;
		++counter;
		static int dir = 2;

		void *data_buff = lock(the_surf, type);

		static int i = 0, z  = 0;
		for(i = 1; i < the_surf->w-1; i++) {
			for(z = 1; z < the_surf->h-1; z++) {
				Uint32 fcol = 0;

				switch(dir) {
					case 1:
						{

				Uint32 c1 = gp(i,z);
				Uint32 c2 = gp(i+1,z+1);
				Uint32 c3 = gp(i,  z+1);
				fcol = c1 + c2 + c3;
				if(fcol != 0) 
					fcol /= 3;

						}
				break;
					case 2:
						{
							Uint32 c1 = gp(i,z);
							Uint32 c2 = gp(i-1,z-1);
							Uint32 c3 = gp(i,  z-1);
							fcol = c1 + c2 + c3;
							if(fcol != 0)
							fcol /= 3;
						}
						break;
				}
				
				Uint8 cc1,cc2,cc3;
				cc1 = (fcol & 0xFF0000) >> 16;
				cc2 = (fcol & 0x00FF00) >> 8;
				cc3 = (fcol & 0x0000FF);
				

				switch(color_dir) {
				case 1:
				fcol = SDL_MapRGB(this->front->format, 0xFF,cc2,cc3);
				break;
				case 2:
				fcol = SDL_MapRGB(this->front->format, cc1,0xFF,cc3);
				break;
				case 3:
				fcol = SDL_MapRGB(this->front->format, cc1, cc2, 0xFF);
				break;
				}


				sp(i+x,z+y,fcol);
				

			}
		}

		unlock(the_surf);


		if(counter > 760 && dir == 1) {
			counter = 0;
			dir = 2;
		}

		if(counter > 250 && dir == 2)
		{
			counter = 0;
			dir = 1;
		}

	}

	void setcdir(int cdir) {
		color_dir = cdir;
	}

protected:
	SDL_Surface *front;
	void        *buffer;
	Uint8       type;
	Uint16      pitch;
	int         color_dir;
	
};


#endif
