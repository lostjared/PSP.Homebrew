

#include"froggy.h"
//#include<memory.h>
#include<stdlib.h>
#include<time.h>

SDL_Surface *cars[11];
SDL_Surface *froggy[7];
SDL_Surface *lilly;
SDL_Surface *rock = 0;
SDL_Surface *turtle;
SDL_Surface *shark, *shark_l;


struct SDL_Font *font = 0;


static char *car_str[] = { "img/bluecar.bmp", "img/bluecar1.bmp", "img/redcar.bmp", "img/silvercar.bmp", "img/greencar.bmp", "img/semi.bmp", "img/semi1.bmp", "img/semi2.bmp", "img/semi3.bmp", "img/pt1.bmp", "img/pt2.bmp",  0 };
static char *froggy_str[] = { "img/ninjafrog.bmp", "img/ninjafrogsmash.bmp", "img/ninjafrogsmashblood.bmp", "img/efrog.bmp", "img/efrogdead1.bmp", "img/efrogdead2.bmp",  0 };
static Uint8 *keys = 0;
static int frame_speed = 550;


int level_speed = 3;
int car_offset = 10;
int do_ani = 0;
int level_counter = 20;


typedef struct _Tile {
	int x,y,w,h,type,dir, off;

} Tile;

SDL_Rect rc_array[3];


typedef struct _Froggy {
	int x,y,lives,cur,score;
} Frog;

Tile map[25];
Frog froggy_s;

void reset_level() ;
Tile turtles[5];
Tile sharks[5];



void SDL_SetRect(SDL_Rect *rc, int x, int y, int w, int h)  {
	rc->x = x, rc->y = y, rc->w = w, rc->h = h;
}

int chk_pos(int z) {

	int i;
	for(i = 0; i < car_offset; i++) {

		SDL_Rect rc = { map[i].x, map[i].y, map[i].w, map[i].h };
		SDL_Rect rc2 = { map[z].x, map[z].y, map[z].w, map[z].h };
		if(sprite_colide(&rc,&rc2))
			return -1;
	
	}

	return 1;

}



void init_frog() {

	froggy_s.x = 480/2;
	froggy_s.y = 272-35;
	froggy_s.cur = 0;
	

}

void SDL_ReverseBlt(SDL_Surface *surf, SDL_Rect *rc, SDL_Surface *front_surf, SDL_Rect *rc2, Uint32 transparent) {

	void *buf , *buf2;
	int i,z,i2,z2;
	buf = lock(surf, surf->format->BitsPerPixel);
	buf2 = lock(front_surf, front_surf->format->BitsPerPixel);

	i2 = rc2->x;
	z2 = rc2->y;

	for(i = rc->w; i > 0; i--) {
		for(z = 0; z < rc->h; z++) {
			SDL_Color col;
			Uint32 color = getpixel(surf, i, z, surf->format->BitsPerPixel, surf->pitch, &col);
			if(color != transparent)
			setpixel(buf2, i2, z2, color, front_surf->format->BitsPerPixel, front_surf->pitch);
			z2++;

		}
		z2 = rc2->y;
		i2++;
	}
}

void draw_frog() {


	static int c = 0;
	
	SDL_Rect rc = { froggy_s.x, froggy_s.y, froggy[froggy_s.cur]->w, froggy[froggy_s.cur]->w };
	if(do_ani == 1) {
		if((++c % 4) == 0) {

			froggy_s.cur ++;
			if(froggy_s.cur >= 2)
			froggy_s.cur = 2, do_ani = 2;
			// reset level
		
		}
	
	}
	else if(do_ani == 3) {

		if((++c % 4) == 0) {

			froggy_s.cur ++;
			if(froggy_s.cur >= 5)
			froggy_s.cur = 5, do_ani = 2;
			// reset level
		
		}
	
	
	}

	SDL_SetColorKey(froggy[froggy_s.cur], SDL_SRCCOLORKEY, SDL_MapRGB(froggy[froggy_s.cur]->format, 255, 0, 0));
	SDL_BlitSurface(froggy[froggy_s.cur], 0, front, &rc);

}

void draw_road() {

	SDL_Rect rc = { 0, 75, 480, 5 };
	SDL_Rect rc2 = { 0, 0, front->w, front->h };
	unsigned char b = 91;

	int i;
	int c = 0;

	SDL_FillRect(front, &rc2, SDL_MapRGB(front->format, 75, 75, 75 ));
	SDL_FillRect(front, &rc, SDL_MapRGB(front->format, 255, 215, 61));	
	{

	SDL_Rect rc =  { 0, 240-5, 480, 5 };
	SDL_FillRect(front, &rc, SDL_MapRGB(front->format, 255, 215, 61));

	}
	SDL_SetRect(&rc, 0, 240+5, 480, 272-240+5);
	SDL_FillRect(front, &rc, SDL_MapRGB(front->format, 75 , 45, 35));
	for(i = 0; i < 75; i++) {
		SDL_SetRect(&rc, 0, i, 480, 1);
		SDL_FillRect(front, &rc, SDL_MapRGB(front->format, 3, 39, --b));
	}

	for(i = 0; i < 480; i += 480/6) {
		SDL_SetRect(&rc, i, 272/2+20, 35, 5);
		SDL_FillRect(front, &rc, SDL_MapRGB(front->format, 255, 255, 255));
	}

	SDL_SetColorKey(rock, SDL_SRCCOLORKEY, SDL_MapRGB(rock->format, 255, 0, 0));
	{
		int i;
		for(i = 0; i < 3; i++)
		SDL_BlitSurface(rock, 0, front, &rc_array[i]);
	
	}

}


void draw_cars() {

	int i;
	for(i = 0; i < 20; i++) {

		if(map[i].off == 1) {

			SDL_Rect rc = { map[i].x, map[i].y , map[i].w, map[i].h };
			SDL_Rect rc2 = { 0, 0, cars[map[i].type]->w-5, cars[map[i].type]->h };
			SDL_SetColorKey(cars[map[i].type], SDL_SRCCOLORKEY, SDL_MapRGB(cars[map[i].type]->format, 255, 0, 0));
			if(map[i].dir == 1) SDL_BlitSurface(cars[map[i].type], 0, front, &rc);
			else SDL_ReverseBlt(cars[map[i].type], &rc2, front, &rc, SDL_MapRGB(cars[map[i].type]->format, 255, 0, 0));
			
		}
	}

}

void draw_turtle() {

	int i;
	for(i = 0; i < 4; i++) {
		SDL_Rect rc = { turtles[i].x, turtles[i].y, turtles[i].w, turtles[i].h };
		SDL_SetColorKey(turtle, SDL_SRCCOLORKEY, SDL_MapRGB(turtle->format, 255, 0, 0));
		SDL_BlitSurface(turtle, 0, front, &rc);
	}
	for(i = 0; i < 2; i++) {

		SDL_Rect rc = { sharks[i].x, sharks[i].y, sharks[i].w, sharks[i].h };
		SDL_SetColorKey(shark, SDL_SRCCOLORKEY, SDL_MapRGB(shark->format, 255, 0, 0));
		SDL_BlitSurface(shark, 0, front, &rc);
	}
	for(i = 2; i < 4; i++) {
		SDL_Rect rc = { sharks[i].x, sharks[i].y, sharks[i].w, sharks[i].h };
		SDL_Rect rc2  = { 0, 0, sharks[i].w, sharks[i].h  };
		SDL_SetColorKey(shark_l, SDL_SRCCOLORKEY, SDL_MapRGB(shark->format, 255, 0, 0));
		SDL_BlitSurface(shark_l, 0, front, &rc);
	
	}
	
}

void draw_lilly() {

/*
	SDL_Rect rc = { 10, 10, lilly->w, lilly->h };
	SDL_SetColorKey(lilly, SDL_SRCCOLORKEY, SDL_MapRGB(lilly->format, 255, 0, 0));
	SDL_BlitSurface(lilly, 0, front, &rc);
*/

}

void game_over() {


}

int sprite_colide(SDL_Rect *rc, SDL_Rect *rc2) {

	int i,z;
	for( i = rc->x; i < rc->x+rc->w; i++) {
		for(z = rc->y; z < rc->y+rc->h; z++) {
			if(i >= rc2->x && i <= rc2->x+rc2->w && z >= rc2->y && z <= rc2->y+rc2->h) return 1;
		}

	}

	return 0;

}

Uint32 Timer_Call(Uint32 interval) {

	if(scr == 1) {
	level_counter--;
	if(level_counter <= 0) {
		reset_level();
		level_counter = 20;
	}
	}

	return interval;
}

void col_detect() {

	int i;
	for(i = 0; i < car_offset; i++) {

		int x,y;
		if(map[i].off == 1 && do_ani == 0)
		{
			SDL_Rect rc = { froggy_s.x, froggy_s.y, froggy[0]->w, froggy[0]->h };
			SDL_Rect rc2 = { map[i].x, map[i].y , map[i].w, map[i].h };

			if(sprite_colide(&rc, &rc2) == 1) {
				do_ani = 1;
				froggy_s.lives--;
				froggy_s.score -= 1500;
				if(froggy_s.score < 0)

				if(froggy_s.lives <= 0)
				game_over();
				return;
			}
		}
	
	}

}

void rand_car(Tile *map) {

	int r = rand()%11;
	int dir = rand()%2;
	if(dir == 0) {
		map->x = 0;
		map->y = 272/2+45;
		map->w = cars[r]->w;
		map->h = cars[r]->h;
		map->type = r;
		map->dir = dir;
		map->off = 0;
	} else {
		map->x = 480-cars[r]->w;
		map->y = 272/2-40;
		map->w = cars[r]->w;
		map->h = cars[r]->h;
		map->type = r;
		map->dir = dir;
		map->off = 0;
	}
}

void init_map() {

	int i;
	srand((unsigned int) time(0));
	memset(map, 0, sizeof(map));
	memset(turtle, 0, sizeof(turtle));

}

void rls_cars() {


	int i, cord_x = -116;
	for(i = 0; i < 3; i++) {
		int r = rand()%11;
		map[i].x = cord_x;
		cord_x += 146;
		map[i].y = 272/2+50;
		map[i].w = cars[r]->w;
		map[i].h = cars[r]->h;
		map[i].type = r;
		map[i].dir = 0;
		map[i].off = 1;
	}

	cord_x = 480+116;
	
	for(i = 3; i < 6; i++) {
		int r = rand()%11;
		map[i].x = cord_x;
		map[i].y = 272/2-45;
		map[i].w = cars[r]->w;
		map[i].h = cars[r]->h;
		map[i].type = r;
		map[i].dir = 1;
		map[i].off = 1;
		cord_x -= 146;
	}

}

void rls_turtle() {

	
	int i;
	int x_cord = -turtle->w;

	for(i = 0; i < 2; i++) {

		turtles[i].x = x_cord;
		sharks[i].x = x_cord+turtle->w+3;
		turtles[i].y = 45;
		sharks[i].y = 45;
		turtles[i].w = turtle->w;
		turtles[i].h = turtle->h;
		sharks[i].w = shark->w;
		sharks[i].h = shark->h;
		turtles[i].off = 1;
		turtles[i].dir = 0;
		x_cord += turtle->w + 90;
	}

	x_cord = 480+turtles->w;
	for(i = 2; i < 4; i++) {

		turtles[i].x = x_cord;
		sharks[i].x = x_cord-turtle->w+3;
	
		turtles[i].y = 25;
		sharks[i].y = 25;

		turtles[i].w = turtle->w;
		turtles[i].h = turtle->h;
		sharks[i].w = shark->w;
		sharks[i].h = shark->h;
		turtles[i].off = 1;
		turtles[i].dir = 0;
		x_cord -= turtle->w + 90;
	
	}



}


int chk_car(int z) {

	int i, counter = 0;
	for(i = 0; i < car_offset; i++) {	
		if(map[i].off == 1)
			counter++;
	}

	if(counter > 2)
		return -1;
	else return 1;
}



void turn_on() {
	int i;

	for(i = 0; i < car_offset; i++) {
		if(map[i].off == 0 && chk_car(i)) {
			if(!chk_car(i)) return;
			rand_car(&map[i]);
			map[i].off = 1;
			return;
		}
	}
}




void movement(int dir) {

	if(do_ani == 2) {
		reset_level();
		return;
	}

	if(do_ani != 0)
		return;

	static int c = 0;
	if((++c % 10) == 0) {
		switch(dir) {
		case 0:// up
		
			if(froggy_s.y <= 10) {
			// level passed
				int i;
				for(i = 0; i < 3; i++) {

					SDL_Rect rc = { froggy_s.x, froggy_s.y, froggy[0]->w, froggy[0]->h };
					if(sprite_colide(&rc, &rc_array[i])) {
				reset_level();
				level_speed--;
				return;
				}


				}

			}
			else froggy_s.y -= 10, froggy_s.score += 50;
		

		break;	
		case 1:// down
		{
	
			if(froggy_s.y <  272-froggy[0]->h)
				froggy_s.y += 10, froggy_s.score -= 50;
		
		}
		break;
		case 2:// left
		{
			if(froggy_s.x > 0) 
				froggy_s.x -= 10;// froggy_s.score += 50;
		}
		break;
		case 3:
		{
			if(froggy_s.x < 480-froggy[0]->w)
				froggy_s.x += 10;//, froggy_s.score -= 50;
		}
		break;
		}
	}

}

void check_input() {

	keys = SDL_GetKeyState(0);

	// keyboard input
	if(keys[SDLK_UP]) 
		movement(0);
	if(keys[SDLK_DOWN]) 
		movement(1);
	if(keys[SDLK_LEFT])
		movement(2);
	if(keys[SDLK_RIGHT])
		movement(3);

	if(SDL_JoystickGetButton(stick, 8)) {
		movement(0);
	}
	if(SDL_JoystickGetButton(stick, 6)) {
		movement(1);
	}
	if(SDL_JoystickGetButton(stick, 7)) {
		movement(2);
	}
	if(SDL_JoystickGetButton(stick, 9)) {
		movement(3);
	}
}


void logic() {
	int i;
	static int car_off = 0;

	static int counter = 0;

	check_input();
	if((++counter % level_speed) != 0) return;

	for(i = 0; i < 20; i++) {

		if(map[i].dir == 0 && map[i].off == 1) {
			map[i].x++;
			if(map[i].x > 480-cars[map[i].type]->w) {
				map[i].x = -cars[map[i].type]->w;
			}
		
		}
		else if(map[i].dir == 1 && map[i].off == 1) {
			map[i].x--;
			if(map[i].x <=  -cars[map[i].type]->w) {
				map[i].x = 480+cars[map[i].type]->w;
			}
		
		}
		
	}

	for(i = 0; i < 2; i++) {

			
		{
			SDL_Rect rc = { turtles[i].x, turtles[i].y, turtles[i].w, turtles[i].h };
			SDL_Rect rc2 = { froggy_s.x, froggy_s.y, froggy[0]->w, froggy[0]->h };
			if(sprite_colide(&rc, &rc2)) {

				froggy_s.x ++;
				if(froggy_s.x >= 480)
				reset_level();

	
			}
		}
		
		turtles[i].x++;
		if(turtles[i].x > 480+turtles[i].w)
			turtles[i].x = -turtles[i].w;
		
	
	}

	for(i = 2; i < 4; i++) {
	
		{
			SDL_Rect rc = { turtles[i].x, turtles[i].y, turtles[i].w, turtles[i].h };
			SDL_Rect rc2 = { froggy_s.x+10, froggy_s.y, froggy[0]->w, froggy[0]->h-10 };
			if(sprite_colide(&rc, &rc2)) {

				froggy_s.x --;
				if(froggy_s.x <= 0)
				reset_level();
	
			}
		}
	
		turtles[i].x--;
		if(turtles[i].x < -turtles[i].w)
			turtles[i].x = 480+turtles[i].w;
	
	}
	for(i = 0; i < 2; i++) {

		sharks[i].x++;
		if(sharks[i].x > 480+sharks[i].w)
			sharks[i].x = -turtles[i].w;

		// chk points
		{
			SDL_Rect rc = { froggy_s.x, froggy_s.y, froggy[0]->w, froggy[0]->h-10 };
			SDL_Rect rc2 = { sharks[i].x, sharks[i].y, sharks[i].w, sharks[i].h };
			if(sprite_colide(&rc, &rc2)) 
				do_ani = 3;
		}
	
	}

	for(i = 2; i < 4; i++) {
		sharks[i].x--;
		if(sharks[i].x < -sharks[i].w)
			sharks[i].x = 480+turtles[i].w;

		// chk points
		{
			SDL_Rect rc = { froggy_s.x, froggy_s.y, froggy[0]->w, froggy[0]->h-10 };
			SDL_Rect rc2 = { sharks[i].x, sharks[i].y, sharks[i].w, sharks[i].h };
			if(sprite_colide(&rc, &rc2)) 
				do_ani = 3;
		}
	}

	
	
	col_detect();
	
}

void render() {


	char buf[256];

	logic();
	draw_road();
	draw_lilly();
	sprintf(buf, "Road Kill - Score: %d , Lives: %d, Time: %d", froggy_s.score, froggy_s.lives, level_counter);
	SDL_PrintText(front, font, 0, 272-20, SDL_MapRGB(front->format, rand()%255,rand()%255,rand()%255), buf);
	draw_turtle();
	draw_frog();
	draw_cars();
	
}


void init() {

	int i;
	for(i = 0; car_str[i] != 0; i++) {
		cars[i] = SDL_LoadBMP(car_str[i]);
		if(!cars[i]) {
			fprintf(stderr, "Error bitmap %s couldnt be loaded", car_str[i]);
		}
	}
	
	for(i = 0; froggy_str[i] != 0; i++) {

		froggy[i] = SDL_LoadBMP(froggy_str[i]);
		if(!froggy[i]) {
			fprintf(stderr, "Error bitmap %s couldnt be loaded", froggy_str[i]);
		}
	
	}

	lilly = SDL_LoadBMP("img/lillypad.bmp");
	rock = SDL_LoadBMP("img/rock.bmp");
	turtle = SDL_LoadBMP("img/turtle.bmp");
	shark = SDL_LoadBMP("img/shark.bmp");
	shark_l = SDL_LoadBMP("img/shark1.bmp");
	font = SDL_InitFont("font/fixed.mxf");

	reset_level();
	froggy_s.lives = 10;
	froggy_s.score = 0;
	//turn_on();
	SDL_SetTimer( 1000, Timer_Call);

}

void free_gfx() {

	int i;
	for(i = 0; car_str[i] != 0; i++)
	SDL_FreeSurface(cars[i]);
	for(i = 0; froggy_str[i] != 0; i++)
	SDL_FreeSurface(froggy[i]);
	SDL_FreeSurface(lilly);
	SDL_FreeFont(font);
	SDL_FreeSurface(rock);
	SDL_FreeSurface(turtle);
	SDL_FreeSurface(shark);
	SDL_FreeSurface(shark_l);


}

void reset_level() {

	int i;
	init_map();
	init_frog();
	do_ani = 0;
	rls_cars();
	rls_turtle();
	for(i = 0; i < 3; i++) {

		SDL_SetRect(&rc_array[i], rand()%480-rock->w, 10, rock->w, rock->h );
	}

	if(froggy_s.lives <= 0)
		scr = 2;
}

void new_game() {
	level_counter = 20;
	froggy_s.lives = 10;
	froggy_s.score = 0;
}

