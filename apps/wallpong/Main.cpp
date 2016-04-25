#include "masterx.h"

/*

  Wall Pong : Tutorial #6 First Mini-Game
  by: Master on LSD ( Jared Bruni )
  http://www.lostsidedead.com/gameprog/

  this demo uses the older C-Style rather then using classes

*/

// the debug defenition for debug information within the executable
//#define iDEBUG 

long  MasterProc(unsigned int, unsigned int, unsigned int, unsigned int);
void update(MASTERSCREEN screen);
void drawintro();
void drawgame();
void drawexit();
void loadgraphics();
void draworb();
void moveball();
void drawscore();


enum { INTRO = 420 , GAME , OVER };
MasterXHWND mxhwnd;
MasterGraphic intro;
MasterGraphic over;
MasterGraphic ball;

int orb_x = 225;
int orb_y = 275;
int bar_x = 100;
int bar_y = 100;
int ball_x = 150;
int ball_y = 150;
bool ball_dir = true;
int  ball_spin = rand()%2;
int  ball_speed = 2;
bool ball_spindir = true;
int lives = 3;
int hits = 0;



int  MasterMain(char *line)
{
	if(mxhwnd.CreateMasterX("WallPong",640,480,COLOR_DEFAULT,MasterProc,0,0,0))
	{
		//ShowCursor(false);
		loadgraphics();
		mxhwnd.SetScreen(INTRO);
		return mxhwnd.InitLoop(update);
	}

	return 0;
}

void loadgraphics()
{
	mxhwnd.LoadGraphic(&intro,"intro.bmp");
	mxhwnd.LoadGraphic(&over,"over.bmp");
	mxhwnd.LoadGraphic(&ball,"ball.bmp");
}

long  MasterProc(unsigned int hwnd, unsigned int msg, unsigned int wParam, unsigned int lParam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{

			if(mxhwnd.GetScreen() == OVER)
			{
				lives = 3;
				hits = 0;
				mxhwnd.SetScreen(GAME);
			}

			switch(wParam)
			{
			case 13:
				{
					switch(mxhwnd.GetScreen())
					{
					case INTRO:
					{
						if(orb_y == 275)
						{
							mxhwnd.SetScreen(GAME);
						}
						else
						{
							mxhwnd.SetScreen(GAME);
						}
					}
						break;
					}
			}

				break;
			}
		}
		break;
	}
	return 0;
}

void update(MASTERSCREEN screen)
{
	switch(screen)
	{
	case INTRO:
		drawintro();

#ifdef iDEBUG
		mxhwnd.text.printtext("intro - debug information",10,10);
#endif
		break;
	case GAME:
		drawgame();
#ifdef iDEBUG
		mxhwnd.text.printtext("game - debug information",10,10);
#endif
		break;
	case OVER:
		drawexit();
#ifdef iDEBUG
		mxhwnd.text.printtext("over - debug information",10,10);
#endif
		break;
	}

#ifdef iDEBUG 
	mxhwnd.text.printtext(" press escape to exit", 10,25);
#endif
}

void drawintro()
{
	intro.DisplayGraphic(0,0);
	draworb();
}

void draworb()
{
	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		orb_y = 325;
	}
	if(mxhwnd.KeyCheck(DIK_UP))
	{
		orb_y = 275;
	}
	ball.DisplayGraphic(orb_x,orb_y);
}

void drawgame()
{
	if(mxhwnd.KeyCheck(DIK_UP))
	{
		if(bar_y > 0)
		{
			bar_y = bar_y - 6;
		}
		else
		{
			bar_y = 0;
		}
	}

	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		if(bar_y < 480-80)
		{
			bar_y = bar_y + 6;
		}
		else
		{
			bar_y = 480-80;
		}
	}
	moveball();
	// drawing the wall
	mxhwnd.paint.mxdrawrect(640-10,0,640,480,RGB(255,255,255),RGB(255,255,255));
	// ddrawing th ebar
	mxhwnd.paint.mxdrawrect(bar_x,bar_y,bar_x+10,bar_y+80,RGB(255,255,255),RGB(255,255,255));
	// drawing the ball
 	//mxhwnd.paint.mxdrawellipse(ball_x,ball_y,ball_x + 10,ball_y + 10,RGB(255,255,255),RGB(255,255,255));
	ball.DisplayGraphic(ball_x,ball_y);

	drawscore();

}

void moveball()
{

	// going left
	if(ball_dir)
	{
		ball_x = ball_x - ball_speed - 4;

	}
	else // going right
	{
		ball_x = ball_x + ball_speed + 4;

	}

	// going up
	if(ball_spindir)
	{
		ball_y = ball_y - ball_spin - 4;
	}
	else // going down
	{
		ball_y = ball_y + ball_spin + 4;

	}
	

	// check if its clipping
	if(ball_x < bar_x + 10)
	{
		if(ball_x > bar_x)
		{

			if(ball_y > bar_y)
			{
				if(ball_y < bar_y + 80)
				{


					if(ball_y < bar_y + 40)
					{
						ball_spindir = true;
					}
					else
					{
						ball_spindir = false;
					}
					hits++;
			// we hit the bar
			ball_dir = false;
			ball_speed = rand()%5;
			if(ball_speed < 2)
			{
				ball_speed = 3;
			}
			ball_spin = rand()%2;

			}
			}

		}
	}

	if(ball_x < 640)
	{
		if(ball_x > 640-20)// for width as well
		{
			ball_dir = true;
			ball_speed = rand()%5;
			if(ball_speed < 2)
			{
				ball_speed = 3;
			}
			ball_spin = rand()%2;
		}
	}

	if(ball_y + 10 > 480)
	{
		ball_spindir = true;
		ball_spin = rand()%2;
	}

	if(ball_y < 0)
	{

		ball_spindir = false;
		ball_spin = rand()%2;
	}


	if(ball_x < 0)
	{
		lives--;

		if(lives <= 0)
		{
			mxhwnd.SetScreen(OVER);
		}
		ball_x = 600;
		ball_y = 150;
		ball_dir = true;
		ball_spindir = true;

	}
}


void drawscore()
{
	char lifebuff[100];
	

	sprintf(lifebuff, "Lives: %d Hits: %d", lives, hits);


	mxhwnd.text.printtext(lifebuff,640/2-50,10);

}


void drawexit()
{
	over.DisplayGraphic(0,0);
}