	
#include"compile_mode.h"

#include"theheader.h"
#include"game.h"


mxHwnd mxhwnd;
mxFont  font;
mxPaint paint;

char stemp[280];

void load(int scr);
void unload();

int linenum = 10;

char *getPath(char *str)
{
return str;
}


class Intro {

	mxSprite logo;
	mxSprite start_scr;
	time_t tha_time, ntime;
	int wait;
	int clock_pos,curc_pos,twait;
public:

	void init()
	{ 
		logo.load(getPath("intro.bmp"));
		start_scr.load(getPath("start.bmp"));
		tha_time = time(0);
		//clock_pos = SDL_GetTicks();
	}
	void update()
	{
		//static unsigned int tick_count = SDL_GetTicks();
		//if(tick_count + 1000 > SDL_GetTicks())
		//{

			logo.display(&mxhwnd,0,0);
		//	return;
		//}
		// screen transition
		for(int i = 0; i < 20000 ; i++)
		{
			int pos1=rand()%logo.sptr->w, pos2 = rand()%logo.sptr->h;
			mxhwnd.setPixel(logo.sptr, pos1, pos2 , mxhwnd.getPixel(start_scr.sptr,pos1,pos2));//rand()%255,rand()%255,rand()%255);
		}

		logo.display(&mxhwnd, 0, 0);
		font.printText(10,10, "Press Enter to Continue.. \n");
		ntime = time(0);
		if(ntime > tha_time)
		{
			tha_time = ntime;
			wait++;
		}
		if(wait > 2)
		{
			wait = 0;
			mxhwnd.setScreen(START);
		}
	}

	void free()
	{
		logo.~mxSprite();
		start_scr.~mxSprite();
	}
};

class Options {

public:
	int lines,full_scr,cur_pos;

	Options()
	{
		lines = 10;
		full_scr = 1;
		cur_pos = 0;
	}
	void init()
	{
	}

	void update()
	{
		paint.drawRect(35,82,621-35,440-70, 0x0);
		char chr[255];
		sprintf(chr, "Amount of Lines Until Speed increase: %d", lines);
		font.printText(70,90,chr);
		sprintf(chr, "Toggle FullScreen : %s", full_scr == 0 ? "On" : "Off");
		font.printText(70,120,chr);
		switch(cur_pos)
		{
		case 0:
			font.printText(40,90,"=)>");
			break;
		case 1:
			font.printText(40,120,"=)>");
			break;
		}

		font.printText(60,300,"Use the arrow keys to toggle the menus");
		font.printText(60,320,"Press Enter to Apply changes Esc to return");
	}

};

class Credits {

public:
	void init()
	{
	}
	void update()
	{
		paint.drawRect(35,82,621-35,440-70,0x0);
		font.printText(40,100,"MasterPiecePSP is written in C++ / SDL - by LostSideDead ");
		font.printText(40,120,"This program is free. ");
		font.printText(40,140,"Click or Press Escape to Return");
	}
};

struct Scores {

	struct SDat {

		char user_name[255];
		int score;
	};
	SDat data[8];
};

class HighScores {
	
	int t_score,pos;
	bool in_score;
	char user_name[255];

public:

	Scores score;

	HighScores()
	{
		init();
		strcpy(user_name,"");
		pos = 0;
		in_score = false;
	}

	~HighScores()
	{
		save();
	}

	void init()
	{
		/*ifstream fin("scores.dat", ios::binary);
		if(fin.is_open())
		{
			fin.read((char*)&score,sizeof(score));
			fin.close();
		}
		else
		{
			for(int v = 0; v <= 7; v++)
			{
				score.data[v].score = 0;
				strcpy(score.data[v].user_name,"Unknown User");
			}
			save();
		}*/
	}

	void save()
	{
		/*
		ofstream fout("scores.dat", ios::binary);
		fout.write((char*)&score,sizeof(score));
		fout.close();*/
	}

	void update()
	{
		paint.drawRect(35,82,621-35,440-70,0x0);
		int start_y = 120;
		char dat[255];
		font.printText(45,90, "High Scores");
		for(int p = 0; p < 8; p++)
		{
			sprintf(dat,"%d) %s: %d", (p+1), score.data[p].user_name, score.data[p].score);
			font.printText(45,start_y,dat);
			start_y += 20;
		}

		if(in_score == true)
		{
			char dat[255];
			sprintf(dat,"%s%s", user_name, rand()%5 > 3 ? "_" : "");
			font.printText(280,120,"Input Name: ");
			font.printText(420,120,dat);
		}
		else
			font.printText(280,120,"Press Enter to continue...");
	}

	void input_score(int t_score)
	{
		in_score = true;
		this->t_score = t_score;
		strcpy(user_name,"");
	}

	void sort()
	{
		int max = 8;
		int pas,compare;

		for(pas = 0; pas < max - 1; pas++)
		{ 
			for(compare = 0; compare < max - 1; compare++)
			{
				if(score.data[compare].score < score.data[compare+1].score)
				{
					Scores::SDat temp;
					temp = score.data[compare];
					score.data[compare] = score.data[compare+1];
					score.data[compare+1] = temp;
				}
			}
		}
	}

	void keypress(int key)
	{
		if(key == 8)
		{
			if(pos - 1 <= 0)
			{
				user_name[pos] = 0;
				pos = 0;
			}
			else
			{
				user_name[--pos] = 0;
			}
		}
		else if (key == 13)
		{
			strcpy(score.data[7].user_name, user_name);
			score.data[7].score = t_score;
			sort();
			in_score = false;

		}
		else
		{
			user_name[pos++] = key;
			user_name[pos] = 0;
		}

	}
	
	bool is_input() const
	{
		return in_score;
	}
};

class Start {


public:

	int cursor_pos;
	Options options;
	Credits credits;
	HighScores scorez;

	void init()
	{
		start_scr.load(getPath("start.bmp"));
		start_scr2.load(getPath("start.bmp"));
		start_cursor.load(getPath("cursor.bmp"), 255,0,255);
		gamebg.load(getPath("gamebg.bmp"));
		cursor_pos = 0;
		options.init();
		credits.init();
	}
	void update()
	{

		start_scr.display(&mxhwnd,0,0);
		switch(mxhwnd.getScreen())
		{
		case START:
			switch(cursor_pos)
			{
			case 0:
				{
					cx = 250;
					cy = 170;
				}
				break;
			case 1:
				{
					cx = 250;
					cy = 170+70;
				}
				break;
			case 2: { cx = 250; cy = 170+70*2; } break;
			case 3: { cx = 250; cy = 170+70*3; } break;
			}
			break;
		case OPTIONS:
			options.update();
			return;
		case CREDITS:
			credits.update();
			return;
		case HIGHSCORES:
			scorez.update();
			return;
		}

		start_cursor.display(&mxhwnd,cx,cy);
	}

	void free()
	{
		start_scr.~mxSprite();
		start_scr2.~mxSprite();
		start_cursor.~mxSprite();
		gamebg.~mxSprite();
	}


	mxSprite start_scr;
	mxSprite gamebg,start_scr2;
private:
	mxSprite start_cursor;
	int cx,cy;

};

Start pstart;
Intro intro;
Game  game;


void mousemove(int x, int y)
{
	// printf("mouse moved to %i %i\n", x , y);

	switch(mxhwnd.getScreen())
	{
	case START:
		if(x > 250 && x < 500 && y > 170 && y < 235)
		{
			pstart.cursor_pos = 0;
		}

		if(x > 250 && x < 618 && y > 265 && y < 320)
		{
			pstart.cursor_pos = 1;
		}

		if(x > 250 && x < 580 && y > 326 && y < 380)
		{
			pstart.cursor_pos = 2;
		}

		if(x > 250 && x < 580 && y > 394 && y < 440)
		{
			pstart.cursor_pos = 3;
		}


		break;
	}

}

void mousedown(int button, int x, int y)
{
	//printf("mouse pressed button %i at pos %i %i\n", button, x ,y);
	switch(mxhwnd.getScreen())
	{
	case INTRO:
		mxhwnd.setScreen(START);
		break;
	case START:
		switch(pstart.cursor_pos)
		{
		case 0:
			game.matrix.init_matrix();
			game.paused = false;
			mxhwnd.setScreen(GAME);
			break;
		case 1:
			mxhwnd.setScreen(OPTIONS);
			break;
		case 2:
			mxhwnd.setScreen(CREDITS);
			break;
		case 3:
			printf("Goodbye..\n");
			mxhwnd.kill();
			break;
		}
		break;
	case CREDITS:
		mxhwnd.setScreen(START);
		break;
	}


}

void keydown(int key)
{
	switch(mxhwnd.getScreen())
	{
	case INTRO:
		if(key == 13)
			mxhwnd.setScreen(START);
		break;
	case START:
		{
			switch(key)
			{
			case 273:
				if(pstart.cursor_pos > 0)
					pstart.cursor_pos--;
				break;
			case 274:
				if(pstart.cursor_pos < 3)
					pstart.cursor_pos++;
				break;
			case 13:
				switch(pstart.cursor_pos)
				{
				case 0:
					game.paused = false;
					game.matrix.init_matrix();
					mxhwnd.setScreen(GAME);
					break;
				case 1:
					mxhwnd.setScreen(OPTIONS);
					break;
				case 2:
					mxhwnd.setScreen(CREDITS);
					break;
				case 3:
// no need				mxhwnd.kill();
					break;
				}
				break;
			}
		}
		break;
	case CREDITS:
		if(key == 27)
			mxhwnd.setScreen(START);
		break;
	case OPTIONS:
		switch(key)
		{
		case 27:
			mxhwnd.setScreen(START);
			break;
		case 273:
			if(pstart.options.cur_pos > 0)
				pstart.options.cur_pos--;
			break;
		case 274:
			if(pstart.options.cur_pos < 1)
				pstart.options.cur_pos++;
			break;
		case 275:
			switch(pstart.options.cur_pos)
			{
			case 0:
				if(pstart.options.lines < 15)
					pstart.options.lines++;
				break;
			case 1:
				if(pstart.options.full_scr == 0)
					pstart.options.full_scr = 1;
				else
					pstart.options.full_scr = 0;
				break;
			}
			break;
		case 276:
			switch(pstart.options.cur_pos)
			{
			case 0:
				if(pstart.options.lines > 5)
					pstart.options.lines--;
				break;
			case 1:// no need for fullscreen
				break;
			}
			break;
		case 13:
			linenum = pstart.options.lines;
			unload();
			//if(mxhwnd.isFullScreen() != pstart.options.full_scr)
			mxhwnd.setfullscreen(pstart.options.full_scr,"MpSDL", 640,480, 32);
			load(START);
			break;
		}
		break;
	case GAME:
		if(key == 27)
			mxhwnd.setScreen(START);
		else if(key == 'p' || key == 'P')
			game.paused = !game.paused;
		game.keypress(key);
		break;
	case HIGHSCORES:
		if(pstart.scorez.is_input())
		{
			pstart.scorez.keypress(key);
		}
		else
		{
			if(key == 13)
			{
				mxhwnd.setScreen(START);
			}
		}
		break;
	}
	//printf("pressed the %i scr := %d\n ", key, mxhwnd.getScreen());
}

void keyup(int key)
{
	//printf("KeyUP : %i\n", key);
}

void onevent(SDL_Event *e)
{
	//printf("event #%d\n", e->type);
	switch(e->type)
	{
	case SDL_KEYDOWN:
		//printf("%d \n",SDL_KEYDOWN);
		break;
	}
}

void render(int screen)
{
	switch(screen)
	{
	case INTRO:
		intro.update();
		break;
	case START:
		pstart.update();
		break;
	case OPTIONS:
		pstart.update(); // options is inside of start
	case CREDITS:
		pstart.update(); // credits is inside of start
		break;
	case HIGHSCORES:
		pstart.update(); // highscores is inside of start
		break;
	case GAME:
		game.update();
		break;
	}
	SDL_Flip(mxhwnd.pscr);

}

void load(int scr)
{

	intro.init();
	pstart.init();
	game.load();
	font.load(&mxhwnd, getPath("arial.mxf"));
	paint.init(&mxhwnd);
	mxhwnd.setScreen(scr);
	mxhwnd.setEventHandler(onevent);
	mxhwnd.setMouseDown(mousedown);
	mxhwnd.setMouseMove(mousemove);
	mxhwnd.setKeydown(keydown);
	mxhwnd.setKeyup(keyup);
}

void unload()
{
	font.~mxFont(); // 
	pstart.free(); //  
	intro.free();
	game.free();
}

#ifndef _PC_MODE_H_
extern "C" int SDL_main(int argc, char **argv);
int SDL_main(int argc, char *argv[])
#else
int main(int argc, char **argv)
#endif
{
	if(mxhwnd.init("MpSDL", 640,480,32, false) != -1)
	{
		srand((int)time(0));
		load(INTRO);
		Joystick stick(0);
		mxhwnd.initLoop(render);
	}
	return (0);
}

void gameover()
{
	mxhwnd.setScreen(HIGHSCORES);
	if(pstart.scorez.score.data[7].score < (int) game.matrix.Game.score)
	{
		pstart.scorez.input_score(game.matrix.Game.score);
	}
}