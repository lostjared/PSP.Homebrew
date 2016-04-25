#include<SDL.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

extern "C" {
	#include<SDL_mxf.h>
}

SDL_Surface *front;
SDL_Surface *card;
SDL_Surface *front_card[4];
SDL_Surface *bg;
SDL_Surface *game_over;
SDL_Surface *answer_img;
SDL_Surface *ico, *fourt_img;


SDL_Joystick *stick;

struct SDL_Font *fnt;


typedef struct _Card {

	int card_type;
	int direction;


} Card;

Card cards[3];
int cur_card = 0;
int rand_card = 0;
int attempts = 0;
int wrong = 0;


enum { SCR_IN, SCR_GAME, SCR_FOURT,  SCR_ANSWER, SCR_INT };
               // 1   &  2   &     3    ==    4
enum { B_START, B_TRI, B_CROSS, B_CIRCLE, B_SQUARE, B_SELECT };

int screen = SCR_IN;
int shuffle = 0;
static int ra = -1;
int answer = 0;
int pyscho_active = 0;

inline void new_game();

inline void init() {
	fnt = SDL_InitFont("font/fixed.mxf");
	card = SDL_LoadBMP("img/tcard.bmp");
	game_over = SDL_LoadBMP("img/gameover.bmp");
	answer_img = SDL_LoadBMP("img/answer.bmp");
	stick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
	bg = SDL_LoadBMP("img/bg.bmp");
	fourt_img = SDL_LoadBMP("img/prettygreen.bmp");

	front_card[0] = SDL_LoadBMP("img/cardfront_t.bmp");
	front_card[1] = SDL_LoadBMP("img/cardfront_x.bmp");
	front_card[2] = SDL_LoadBMP("img/cardfront_o.bmp");
	front_card[3] = SDL_LoadBMP("img/cardfront_s.bmp");
	memset(cards, 0, sizeof(cards));
	srand((unsigned int) time(0));
	if(ra == -1)
		ra = rand()%2;

	new_game();
}

inline void new_game() {
	attempts = 1;
	wrong = 0;
	screen = SCR_IN;
	pyscho_active = 0;
}

inline void shuffle_cards(Card *cardz) {

	unsigned int i, r;
	int card_types[3];

	memset(card_types, 0, sizeof(card_types));

	int off = 0;
		do {
			r = rand()%4;
			for(i = 0; i < 3; i++) {
				if(card_types[i] == 0)
				{
					int ok = 0;
					for(unsigned int i = 0; i < 3; i++) {
						if(card_types[i] != r) continue;
						else { ok = 1; break; }
					}

					if(ok == 0)
					{
						card_types[off++] = r;
						break;
					}
				}
			}

			if(off >= 3) break;

		} while ( 1 );

		for(i = 0; i < 3; i++) {
			cardz[i].card_type = card_types[i];
		}

		do { cur_card = rand()%4; } while ( cur_card == 0 );
		do { rand_card = rand()%4; } while ( rand_card == 0 );
}

inline void dump_cards(Card *cardz) {
	printf("Shuffle'n\n");
	for(unsigned int i = 0; i < 3; i++) {
		printf("Card Index (%d) Value (%d)\n", i, cardz[i].card_type);
	}
	printf("------------------------------\n");
}

inline void free() {
	SDL_FreeFont(fnt);
	SDL_FreeSurface(card);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(game_over);
	SDL_FreeSurface(answer_img);
	SDL_FreeSurface(ico);
	SDL_FreeSurface(fourt_img);
	for(unsigned int i = 0; i < 4; i++) {
		SDL_FreeSurface(front_card[i]);
	}
	SDL_JoystickClose(stick);
}



inline void movement(int dir) {

	switch(screen) {
		case SCR_IN:
			switch(dir) {
			case B_START:
				screen = SCR_GAME;
				shuffle = 1;

				break;
			}
			break;
		case SCR_GAME:
			{
				switch(dir) {
				case B_SELECT:
					shuffle = 0;
					shuffle_cards(cards);
					dump_cards(cards);
					break;
				}
            }
			break;
		case SCR_ANSWER:
			{
				switch(dir) {
				case B_START:
					if(shuffle != 1) {
					shuffle = 1;
					attempts++;
					if(attempts >= 10)
						screen = SCR_FOURT;
					else
						screen = SCR_GAME;
					}
					break;
				}

			}
			break;
	}
}

inline void chk_in() {


	Uint8 *keys = 0;
	static int c = 0;

	if((++c % 4) == 0) {
		
		keys = SDL_GetKeyState(0);
		if(keys[SDLK_SPACE])
			movement(B_START);
		if(keys[SDLK_x])
			movement(B_CROSS);
		if(keys[SDLK_t])
			movement(B_TRI);
		if(keys[SDLK_o])
			movement(B_CIRCLE);
		if(keys[SDLK_RETURN])
			movement(B_SELECT);
	}

}

inline void input_down(int d) {


	switch(screen) {
		case SCR_GAME:
		if(shuffle == 1) return;
		if(cur_card == d && rand_card == cur_card) {
			screen = SCR_ANSWER;
			answer = 1;
		}
		else screen = SCR_ANSWER, answer = 0;

		if(d == B_CIRCLE)
		wrong++;
		break;
		case SCR_FOURT:
			{
				static int counter = 0;
				if(pyscho_active == 1) {
					if(d == B_CIRCLE)
					{
						counter++;
						if(counter >= 3) {
							screen = SCR_INT;

						}
					} else counter = 0;

				}
				else {
					new_game();
				}
			}
			break;
		}
}
		
inline void render_intro() {



	static int card_x = 0;
	static int card_y = 0;


	SDL_BlitSurface(bg, 0, front, 0);

	for(unsigned int i = 0; i < 3; i++) {

	SDL_Rect rc = { card_x+i*25, card_y+i*25, 0, 0 };
	SDL_BlitSurface(card, 0, front, &rc);

	}

	SDL_PrintText(front, fnt, 10,10, SDL_MapRGB(front->format, 0, 0, 0), "Master's Intution Builder ");
	SDL_PrintText(front, fnt,  200, 100, SDL_MapRGB(front->format, 255, 0, 0), "Press Start to Play");


}

inline void manip() {

	void *buf = lock(bg, bg->format->BitsPerPixel);

	static int wait = 0;

	if((++wait % 100) != 0) { 
		SDL_BlitSurface(bg, 0, front, 0);
		return;
	}

	unsigned int i,z;

	for(i = 0; i < bg->w; i++) {

		for(z = 0; z < bg->h; z++) {

			SDL_Color col;
			Uint32 color;

			color = getpixel(bg, i, z, bg->format->BitsPerPixel, bg->pitch, &col);
			
			if(ra == 1) 
				color++;
			 else 
				color--;
			setpixel(buf, i, z, color, bg->format->BitsPerPixel, bg->pitch);
		}

	}


	unlock(bg);

	SDL_BlitSurface(bg, 0, front, 0);
}


inline void render_game() {


	manip();

	if(shuffle == 0) {
		SDL_Rect rc1 = { 40, 40, 0, 0 }, rc2 = { 65, 40, 0, 0 }, rc3 = { 90, 40, 0, 0 };
		SDL_BlitSurface(card, 0, front, &rc1);
		SDL_BlitSurface(card, 0, front, &rc2);
		SDL_BlitSurface(card, 0, front, &rc3);
		SDL_Rect rc = { 40, 30+card->h+10, 130, 20 };
		SDL_FillRect(front, &rc, 0);
		SDL_PrintText(front, fnt, 44, 35+card->h+10, SDL_MapRGB(front->format, 255, 0, 0), "T");
		SDL_PrintText(front, fnt, 65, 35+card->h+10, SDL_MapRGB(front->format, 0, 255, 0), "X");
		SDL_PrintText(front, fnt, 95, 35+card->h+10, SDL_MapRGB(front->format, 0, 0, 255), "S");
		SDL_PrintText(front, fnt, 95+25, 35+card->h+10, SDL_MapRGB(front->format, 255, 255, 255), "C");
		SDL_PrintText(front, fnt, 10, 10, ra == 0 ? SDL_MapRGB(front->format, 100, 100, 100) : SDL_MapRGB(front->format, 255,255,255), "Guess a Shape");
		SDL_Rect rcz = { 270, 50, 150, 150 };
		static Uint32 bg_col = SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255);
		SDL_FillRect(front, &rcz, bg_col);
		SDL_PrintText(front, fnt, 275, 55, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "Shape to Guess");
		SDL_Rect rc_lsd = { 295, 75, front_card[0]->w, front_card[0]->h };
		SDL_BlitSurface(front_card[cur_card-1], 0, front, &rc_lsd);
	
	}
	else {
		static int shuffle_x = 40, shuffle_x2 = 40;
		static int direction = 0;

		for(unsigned int i = 0; i < 3; i++) {

			SDL_Rect rc = { cards[i].direction == 0 ? shuffle_x+i*25 : shuffle_x2+i*25, 40, card->w, card->h };
			SDL_BlitSurface(card, 0, front, &rc);

		}

		
		shuffle_x+=10;
		shuffle_x2-=10;


		if(shuffle_x > front->w) {
			direction++;
			if(direction > 1) direction = 0;
			shuffle_x = 0;
			cards[rand()%3].direction = direction;
		}
		if(shuffle_x2 < 0)
		{
			direction++;
			if(direction > 1) direction = 0;
			shuffle_x2 = 480-card->w;
			cards[rand()%3].direction = direction;
		}

		SDL_PrintText(front, fnt, 10, 10, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "Press Select to Stop Shuffle");
		
	}

	static char buf[35];
	sprintf(buf, "Attempts %d/10\n", attempts);
	SDL_PrintText(front, fnt, 310, 10, SDL_MapRGB(front->format, 255, 0,0 ), buf);
	

}

inline void render_answer() {

	SDL_BlitSurface(answer_img, 0, front, 0);
	if(answer == 1)
	SDL_PrintText(front, fnt, 100, 100, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "You are correct!");
	else
	SDL_PrintText(front, fnt, 100, 100, SDL_MapRGB(front->format, 255, 255, 255), "You guessed wrong");

	static char buf[256];
	sprintf(buf, "Current Intution Level %d0%%", 10-wrong);
	SDL_PrintText(front, fnt, 100, 150, SDL_MapRGB(front->format, 250, 220, 057), buf);
	SDL_PrintText(front, fnt, 100, 220, SDL_MapRGB(front->format, 255, 255, 255), "Press Select to Shuffle Agian");
}

inline void render_fourtne() {

	SDL_BlitSurface(fourt_img, 0, front, 0);
	char buf[256];

	switch(wrong) {
		case 0:
			sprintf(buf,"Your intution level is strong or was it luck?");
		break;
		case 1:
			sprintf(buf, "Close but no cigar");
		break;
		case 2:
			sprintf(buf, "Idea so complex cannot grasp in whole");
			break;
		case 3:
			sprintf(buf, "1 & 1 & 1 = 3 Use the pattern to unlock");
			pyscho_active = 1;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			sprintf( buf,"Try agian ");
		break;
	}

	SDL_PrintText(front, fnt, 23, 23, SDL_MapRGB(front->format, 255, 255, 255), buf);
}


void lostalgo(SDL_Surface *surf, int direction,float random, long trip) {

	unsigned int i,z;
	void *buf;
	float speed = 1.0f;

	buf = lock(surf, surf->format->BitsPerPixel);
	for(i = 0; i < surf->w; i++) {
		for(z = 0; z < surf->h; z++) {
			Uint32 color;
			SDL_Color col;
			color = getpixel(surf, i,z,surf->format->BitsPerPixel, surf->pitch, &col);
			trip++;
			if(trip > 3) 
			color += (Uint32) sinf(speed), trip = 0;
			else 
			color += (Uint32) cosf(speed);
			speed += (Uint32)0.5f;
			setpixel(buf,i,z,color+direction,surf->format->BitsPerPixel, surf->pitch);
		}
	}
	unlock(surf);
}

inline void render_intution() {

	static int direction = 0;
	static float random = 1000000.0f;
	static long trip = 0;

	direction++;
	random -= 0.1f;
	trip++;
	lostalgo(fourt_img, direction, random, trip);
	SDL_BlitSurface(fourt_img, 0, front, 0);
	
}

inline void render(int scr) {

	switch(scr) {
		case SCR_IN:
			render_intro();
			break;
		case SCR_GAME:
			render_game();
			break;
		case SCR_FOURT:
			render_fourtne();
			break;
		case SCR_ANSWER:
			render_answer();
			break;
		case SCR_INT:
			render_intution();
			break;
	}

	chk_in();
}


int main(int argc, char **argv) {

	static SDL_Event e;
	int active = 1;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0)
		return -1;

	ico = SDL_LoadBMP("img/ico.bmp");
	SDL_WM_SetIcon(ico, 0);

	front = SDL_SetVideoMode(480,272,0,0);
	if(!front)
		return -2;

	SDL_WM_SetCaption("Master's Intution Builder", 0);


	init();

	while(active == 1) {

		SDL_FillRect(front, 0, 0);
		render(screen);

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
				case SDL_KEYDOWN:
					{
						if(screen == SCR_GAME) {
							if(e.key.keysym.sym == SDLK_t) 
								input_down(B_TRI);
							else if(e.key.keysym.sym == SDLK_s)
								input_down(B_SQUARE);
							else if(e.key.keysym.sym == SDLK_c)
								input_down(B_CIRCLE);
							else if(e.key.keysym.sym == SDLK_x)
								input_down(B_CROSS);
						}
						else if (screen == SCR_FOURT) {
							if(e.key.keysym.sym == SDLK_c)
								input_down(B_CIRCLE);
							else
								input_down(B_CROSS);
						}
						else if(screen == SCR_INT)
							if(e.key.keysym.sym == SDLK_RETURN) screen = SCR_IN;
					}
					break;
				case SDL_JOYBUTTONDOWN:
					{


					}
					break;
			}
		}

		SDL_Flip(front);

	}

	free();
	SDL_FreeSurface(front);
	SDL_Quit();

	return 0;
}


