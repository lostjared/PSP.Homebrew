/* SuperMaster
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#define FOR_PSP

#include"thehead.h"// grateful as can be
#ifdef FOR_PSP
#include <pspkerneltypes.h>	//# |_ For 333Mhz Overclock
#include <psppower.h>		//# |
#endif
MasterXHWND mxhwnd;
Intro intro;
Start start;
Game  game;
GameOver over;
Launch launch;

long event(unsigned int hwnd,unsigned int msg,unsigned int wParam,unsigned int lParam);
void render(int screen);
inline void init();
int MasterMain(char* line) 
{

#ifdef FOR_PSP
	scePowerSetClockFrequency(333, 333, 166); //# overclocked
#endif

	if(mxhwnd.CreateMasterX("MasterX",480,272,COLOR_DEFAULT,event,0,0,0))
	{
		init();
		mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void init()
{
	intro.load();
	start.load();
	game.load();
	over.load();
	launch.load();

	mxhwnd.HideCursor();
	mxhwnd.SetScreen(ID_INTRO);	
}



long  event(unsigned int hwnd,unsigned int msg,unsigned int wParam,unsigned int lParam)
{

	switch(msg)
	{
	
	case WM_KEYDOWN:
		{

			switch(mxhwnd.GetScreen())
			{
			case ID_START:
				start.keypress(wParam);
				break;
			case ID_GAMEOVER:
				{
					over.keypress(wParam);
				}
				break;
			case ID_LAUNCH:
				{
					launch.keypress(wParam);
				}
				break;
			}
		
		}
		break;
	case WM_KEYUP:
		{
			game.keyup(wParam);
		}
		break;

	}

	return (0);
}

void render(int  screen)
{
	switch(screen)
	{
	case ID_INTRO:
		intro.update();
		break;
	case ID_START:
		start.update();
		break;
	case ID_GAME:
		game.update();
		break;
	case ID_GAMEOVER:
		over.update();
		break;
	case ID_LAUNCH:
		launch.update();
		break;
	}
	
}

inline void GetPointFromPos(int pos,int& x, int& y)
{
	x = 0;
	y = 0;
	
	static int startby = 75;
	static int bx,by;
	static int i;
	bx = 50; by = startby;
	int gcount = 0;
	
	
	for(i = 0; i < 700-4+24; i++)
	{
		if(i == pos)
		{
			x = bx;
			y = by;
			return;
		}
		
		by = by + 16;
		gcount++;
		if(gcount > 23)
		{
			gcount = 0;
			by = startby;
			bx = bx + 16;
		}
		
	}
}

int getoff_set()
{
	return game.getoffset();
}


void scrollleft()
{
	game.moveleft();
}

void scrollright()
{
	game.moveright();
}

void releaseparticle(int pos, int type,bool dir)
{
	game.emiter.releaseparticle (pos,type,dir);
}

void newgame()
{
	game.resetgame();
	cur_level = 1;

}

void load_level(char* levelstr)
{
	game.loadlevel(levelstr);
}


void setcredits()
{
	mxhwnd.SetScreen(ID_START);
	start.screen = 1;
}