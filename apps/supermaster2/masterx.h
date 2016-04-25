#ifndef _MASTERX_H_
#define _MASTERX_H_

#include<SDL.h>
extern "C" {
#include<SDL_mxf.h>
}
#include<stdarg.h>
#include<stdlib.h>

extern int MasterMain(char *line);
#define MASTERSCREEN int
#define VK_DOWN SDLK_DOWN
#define VK_UP SDLK_UP
#define VK_LEFT SDLK_LEFT
#define VK_RIGHT SDLK_RIGHT
#define VK_A 'a'
#define VK_S 's'
#define VK_RETURN SDLK_RETURN
#define DIK_A 'a'
#define DIK_S 's'
#define DIK_UP SDLK_UP
#define DIK_LEFT SDLK_LEFT
#define DIK_RIGHT SDLK_RIGHT
#define DIK_DOWN SDLK_DOWN

SDL_Surface *front = 0;

inline Uint32 RGB(unsigned char r, unsigned char g, unsigned char b) {
	return SDL_MapRGB(front->format, r, g, b);
}

enum { ID_INTRO, ID_START, ID_GAME, ID_GAMEOVER, ID_LAUNCH };


class MasterScreen {
public:

	SDL_Surface *front;
	SDL_Surface *back;
	MasterScreen() {
		front = 0;
	}
	~MasterScreen() {
	}
};

class MasterText
{
public:
	MasterScreen*  scr;
	SDL_Font *font;
	Uint32 bk;
	Uint32 text;

	MasterText() {
		font = SDL_InitFont("t.mxf");
	}

	~MasterText() {
		if(font) {
			SDL_FreeFont(font);
			font = 0;
		}
	}


	inline void MasterText::init(MasterScreen *scr) {
		this->scr = scr;
	}

	inline void MasterText::printtext(char *str, int x, int y) {
		SDL_PrintText(scr->front, font, x,y, text, str);
	}

	inline void MasterText::sprinttext(int x, int y, char *str, ...) {
		char text[5000];
		va_list list;
		va_start(list, str);
		vsprintf((char*)text,str,list);
		va_end(list);
		printtext(text, x,y);
	}

	inline void MasterText::printtextrect(char *str, int x, int y, int w, int h) {
		printtext(str, x,y);
	}

	inline void MasterText::printtextunderline(char *str, int x, int y) {
		printtext(str, x,y);
	}

	inline void MasterText::setbkcolor(Uint32 color) {
		// removed only left here for backwards compatbility
	}

	inline void MasterText::settextcolor(Uint32 color) {
		this->text = color;
	}

	inline void MasterText::setfont(SDL_Font *font) {
		this->font = font;
	}

	inline void MasterText::setdefaultfont() {
		// to do

	}

	inline void MasterText::setunderfont(SDL_Font *font) {
		// to do
	}
};

typedef class MasterGraphic
{
	MasterScreen* scr;
	SDL_Surface *surf;
	char  filename[50];
	bool ckey;
	Uint32 color_key;
public:
	int w;
	int h;
	inline void MasterGraphic::init(MasterScreen* scr) {
		this->scr = scr;
		color_key = 0;
	}
	inline bool MasterGraphic::LoadGraphic(char* filename) {
		surf = SDL_LoadBMP(filename);
		w = surf->w;
		h = surf->h;
		return true;
	}
	inline bool MasterGraphic::LoadGraphic(char* filename,MasterScreen* scr) {
		init(scr);
		this->LoadGraphic(filename);
		w = surf->w;
		h = surf->h;
		return true;
	}
	inline void MasterGraphic::ReLoadGraphic() {
		// left for backwards compatiblity
	}
	inline void MasterGraphic::SetColorKey(Uint32 r) {
		color_key = r;
	}
	inline void MasterGraphic::DisplayGraphic(int x, int y) {
		if(surf) {
		SDL_Rect rc = { x,y,surf->w, surf->h };
		SDL_SetColorKey(surf, SDL_SRCCOLORKEY, SDL_MapRGB(surf->format, 255, 255, 255));
		SDL_BlitSurface(surf, 0, scr->front, &rc);
		}
	}
	inline void MasterGraphic::DisplayGraphicEx(int bx, int by, int bw, int bh,int image_x, int image_y) {
		if(surf) {
		SDL_Rect rc = { bx,by,bw,bh };
		SDL_Rect rc2 = { image_x, image_y, bw, bh };
		SDL_SetColorKey(surf, SDL_SRCCOLORKEY, SDL_MapRGB(surf->format, 255, 255, 255));
		SDL_BlitSurface(surf, &rc, scr->front, &rc2);
		}
	}
	MasterGraphic::~MasterGraphic() {  if(surf) SDL_FreeSurface(surf); surf = 0; }
	MasterGraphic::MasterGraphic() { surf = 0; }
	inline void MasterGraphic::Release() {

	}
}MasterSprite;

// left for backwards compatiblity

class MasterSound
{
public:
	inline bool MasterSound::LoadSound(void * pds,char *name) {
		return true;
	}

	inline bool MasterSound::LoadSoundEx(char filename[]) {
		return true;
	}
	inline void MasterSound::Play() {
	}
	inline bool MasterSound::PlayStatus() {
	}
	inline void MasterSound::Release() {
	}
	MasterSound::MasterSound() {}
	MasterSound::~MasterSound() {}
};

// i didnt implement all the drawing algoirthms i was too lazy
class MasterPaint
{
	MasterScreen* scr;
public:

	void MasterPaint::init(MasterScreen *scr) {
		this->scr = scr;
	}

	void MasterPaint::mxanglearc(int x, int y, long radius, float startangle, float sweepangle, Uint32 outline) {
	//	__mxhwnd.paint.drawanglearc (x,y,radius,startangle,sweepangle,outline,outline);
	}

	void  MasterPaint::mxdrawrect(int x, int y, int x2, int y2,Uint32 fill,Uint32 outline) {
	//	__mxhwnd.paint.drawrect(x,y,x2,y2,D3DCOLOR_XRGB(GetRValue(fill),GetGValue(fill),GetBValue(fill)));
		SDL_Rect rc = {x,y,x2-x,y2-y};
		SDL_FillRect(scr->front, &rc, outline);
	}
	void  MasterPaint::mxdrawroundrect(int x, int y, int x2, int y2,int cw, int ch, Uint32 fill,Uint32 outline) {
	//	__mxhwnd.paint.drawroundrect(x,y,x2,y2,cw,ch,fill,outline);
	}
	void  MasterPaint::mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,Uint32 fill, Uint32 outline) {
	//	__mxhwnd.paint.drawpie(x,y,x2,y2,nx,ny,nx2,ny2,fill,outline);
	}
	void  MasterPaint::mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, Uint32 fill, Uint32 outline) {
	//	__mxhwnd.paint.drawchord(x,y,x2,y2,nx,ny,nx2,ny2,fill,outline);
	}
	void  MasterPaint::mxdrawellipse(int x, int y, int x2, int y2,Uint32 fill,Uint32 outline) {
	///	__mxhwnd.paint.drawellipse(x,y,x2,y2,fill,outline);
	}
	void  MasterPaint::mxsetpixel(int x, int y, Uint32 rgbval) {
		void *buf = lock(scr->front,scr->front->format->BitsPerPixel);
		setpixel(buf, x,y,rgbval, scr->front->format->BitsPerPixel, scr->front->pitch);
		unlock(scr->front);
	//	__mxhwnd.paint.drawpixel(x,y,rgbval);
	}
	Uint32  MasterPaint::mxgetpixel(int x, int y) {
	//	return __mxhwnd.paint.drawgetpixel(x,y);
		void *buf = lock(scr->front,scr->front->format->BitsPerPixel);
		SDL_Color col;
		Uint32 color = getpixel(scr->front, x,y, scr->front->format->BitsPerPixel, scr->front->pitch, &col);
		unlock(scr->front);
		return color;
	}
	void  MasterPaint::mxarc(int x1,int x2, int x3, int x4, int x5, int x6, int x7, int x8,Uint32 fill,Uint32 outline) {
	//	__mxhwnd.paint.drawarc(x1,x2,x3,x4,x5,x6,x7,x8,fill,outline);
	}
	void  MasterPaint::mxpolygon(const SDL_Rect* point,int n_points,Uint32 fill,Uint32 outline) {
	//	__mxhwnd.paint.drawpolygon(point,n_points,fill,outline);
	}
	void  MasterPaint::mxlineto(int x, int y,Uint32 fill,Uint32 outline) {
		//__mxhwnd.paint.drawlineto(x,y,fill,outline);
	}
	void  MasterPaint::mxhorizontalline(int x, int x2, int y,Uint32 color) {
    //	__mxhwnd.paint.drawrect(x,y,x2,y+1,D3DCOLOR_XRGB(GetRValue(color),GetGValue(color),GetBValue(color)));
	}
	void  MasterPaint::mxverticalline(int y1,int y2,int x,Uint32 color) {
	//	__mxhwnd.paint.drawrect(x,y1,x+1,y2,D3DCOLOR_XRGB(GetRValue(color),GetGValue(color),GetBValue(color)));
	}
	void  MasterPaint::mxline(int start_x, int start_y, int stop_x, int stop_y,Uint32 color) {
	//	__mxhwnd.paint.drawline(start_x,start_y,stop_x,stop_y,color);
	}
};

enum DisplayColor { COLOR_DEFAULT = 1 };

#define WM_KEYDOWN 1
#define WM_KEYUP 2
#define WM_LBUTTONDOWN 3
#define WM_LBUTTONUP 4
#define WM_ACTIVATEAPP 5

class MasterXHWND
{
	int mscr;

	int pre_time;
	int timer_count;

	bool time_flag;
	bool full_flag;

public:
	int hwnd;
	MasterScreen scr;
	MasterText   text;
	MasterPaint  paint;
//	MasterMedia  media;
	SDL_Joystick *stick;
	SDL_Surface *back;
	long (*event)(unsigned int, unsigned int, unsigned int, unsigned int);
	bool alive;
	unsigned int activeapp;
	bool stretch;
	MasterXHWND() { full_flag = true; }
	~MasterXHWND() { SDL_Quit(); }
	void setfullflag(bool flag) {
		this->full_flag = flag;
	}

	inline bool MasterXHWND::CreateMasterX(char* mytitle,int width,int height,DisplayColor color,long (*event)(unsigned int, unsigned int, unsigned int, unsigned int),int instance,int icon,int cursor) {
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
		stick = SDL_JoystickOpen(0);
		SDL_JoystickEventState(SDL_ENABLE);
		this->scr.front = SDL_SetVideoMode(width,height, 0, 0);
		front = this->scr.front;
		this->event = event;
		text.init(&scr);
		paint.init(&scr);
		if(scr.front) {

			SDL_FillRect(scr.front, 0, 0);
			text.settextcolor(RGB(255,255,255));
			text.printtext("Loading...", 0,0);
			SDL_UpdateRect(scr.front, 0, 0, scr.front->w, scr.front->h);
			return true;
		}
		return false;
	}
	inline unsigned int MasterXHWND::InitLoop( void (* render) (int xscr)) {
		
		static SDL_Event e;
		alive = true;

		while( alive == true ) {
			if(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:
						alive = false;
						break;
					case SDL_KEYDOWN:
						{
							this->event(0, WM_KEYDOWN, e.key.keysym.sym, 0);
						}
						break;
					case SDL_KEYUP:
						{
							this->event(0, WM_KEYUP, e.key.keysym.sym, 0);
						}
                        break;
				
					case SDL_JOYBUTTONDOWN:
						{
							/*
						0 Triangle
						1 Circle
						2 Cross
						3 Square
						4 Left trigger
						5 Right trigger
						6 Down
						7 Left
						8 Up
						9 Right
						10 Select
						11 Start
						12 Home
						13 Hold
						*/
							int key = 0;
							switch(e.jbutton.button) {
							case 0:
								key  = VK_RETURN;
								break;

							case 2:
								key = VK_A;
								break;
							case 3:
								key = VK_S;
								break;
							case 7:
								key = VK_LEFT;
								break;
							case 8:
								key = VK_UP;
								break;
							case 9:
								key = VK_RIGHT;
								break;
							case 6:
								key = VK_DOWN;
							}
							this->event(0, WM_KEYDOWN, key, 0);

						}
						break;
					case SDL_JOYBUTTONUP:
						{
							int key = 0;
						switch(e.jbutton.button) {
							case 0:
								key  = VK_RETURN;
								break;

							case 2:
								key = VK_A;
								break;
							case 3:
								key = VK_S;
								break;
							case 7:
								key = VK_LEFT;
								break;
							case 8:
								key = VK_UP;
								break;
							case 9:
								key = VK_RIGHT;
								break;
							case 6:
								key = VK_DOWN;
							}
							this->event(0, WM_KEYUP, key, 0);

						}
						break;
				}

			}

			SDL_FillRect(scr.front, 0, 0);
			render(mscr);
			SDL_UpdateRect(scr.front, 0, 0, scr.front->w, scr.front->h);

		}


		SDL_JoystickClose(stick);
		SDL_FreeSurface(back);
		SDL_FreeSurface(scr.front);
		SDL_Quit();
		return 0;

	}
	inline void MasterXHWND::Kill() {
		alive = false;
	}
	inline int MasterXHWND::GetScreen() {
		return this->mscr;
	}
	inline void MasterXHWND::SetScreen(int xmscr) {
		this->mscr = xmscr;
		static int prev_scr = 0;

		if(stretch == false && this->mscr != ID_INTRO && this->mscr != ID_START && this->mscr != ID_GAMEOVER &&  this->mscr != ID_LAUNCH) {
			SDL_FreeSurface(scr.front);
			scr.front = SDL_SetVideoMode(640,480,0,0);
			front = scr.front;
			prev_scr = ID_GAME;
			stretch = true;
		}
		else if(prev_scr == ID_GAME && this->mscr != ID_LAUNCH && stretch == false) {
			prev_scr = 0;
			scr.front = SDL_SetVideoMode(480,272,0,0);
			front = scr.front;
		}
		
	}

	inline void MasterXHWND::trade_surfaces() {

	}

/*	inline LRESULT MasterXHWND::SendMasterMessage(UINT msg,WPARAM wParam,LPARAM lParam) {
		return SendMessage(__mxhwnd.hwnd,msg,wParam,lParam);
	}*/
	inline void MasterXHWND::clear() {}
	inline void MasterXHWND::mx_update() {}

	inline bool MasterXHWND::LoadGraphic(MasterGraphic* g, char* filename) {
		return g->LoadGraphic(filename,&scr);
	}
	inline bool MasterXHWND::LoadSound(MasterSound* s,char resourceID[]) {
		return s->LoadSoundEx(resourceID);
	}
	inline bool MasterXHWND::KeyCheck(int key) {
//		return __mxhwnd.input.key.KeyCheck(key);
		Uint8 *keys = SDL_GetKeyState(0);
		if(keys[key])
			return true;
		
		int button = 0;
		switch(key) {
			case VK_LEFT:
				button = 7;
				break;
			case VK_RIGHT:
				button = 9;
				break;
			case VK_DOWN:
				button = 6;
				break;
			case VK_UP:
				button = 8;
				break;
			case VK_A:
				button = 2;
				break;
			case VK_S:
				button = 3;
				break;
			case VK_RETURN:
				button = 0;
				break;
		}

		if(SDL_JoystickGetButton(stick,button)) 
			return true;
		

		return false;
	}

	int GetFX(int w,int x, int nw) {
		float xp = (float)x * (float)w / (float)nw;		
		return (int)xp;
	}

	int GetFZ(int h, int y, int nh) {
		float yp = (float)y * (float)h / (float)nh;
		return (int)yp;
	}

	void stretch_blt(SDL_Surface *surf, SDL_Rect *rc, SDL_Surface *where, SDL_Rect *rc2) {
		int i,z;
		void *buf, *buf2;

		SDL_FillRect(where, 0, 0);
		buf = lock(surf, surf->format->BitsPerPixel);
		buf2 = lock(where, surf->format->BitsPerPixel);

		for(i = 0; i < rc2->w; i++) {
			for(z = 0; z < rc2->h; z++) {
				static unsigned long color = 0;
				static int cx, cy;
				cx = GetFX(rc->w, i, rc2->w);
				cy = GetFZ(rc->h, z, rc2->h);
				SDL_Color col;
				color = getpixel(surf, cx,cy,surf->format->BitsPerPixel, surf->pitch, &col);
				if(color != 0)
				setpixel(buf2, i, z, color, where->format->BitsPerPixel, where->pitch);
			}
		}

		unlock(where);
		unlock(surf);

	}


	inline bool MasterXHWND::AsyncKeyCheck(int key) {
		//if(GetAsyncKeyState(key))
		//	return true;
		Uint8 *keys = SDL_GetKeyState(0);
		if(keys[key])
			return true;
		return false;
	}

	SDL_Surface *create_buffer(int w, int h) {
				return SDL_CreateRGBSurface(SDL_HWSURFACE, w,h, scr.front->format->BitsPerPixel,scr.front->format->Rmask, scr.front->format->Gmask, scr.front->format->Bmask, scr.front->format->Amask);
	}

	inline void MasterXHWND::InitTimer(int id, int interval) {
		//SetTimer(__mxhwnd.hwnd,id,interval,NULL);
	}
	inline void MasterXHWND::DestroyTimer(int id) {
		//KillTimer(__mxhwnd.hwnd,id);
	}
	inline void MasterXHWND::GetMousePosWin(long& x, long& y) {
		x = 0, y = 0;
	}
	inline void MasterXHWND::HideCursor() {
	
	}
	inline void MasterXHWND::RestoreCursor() {
	}
	inline bool MasterXHWND::TimeChange() {
		if(pre_time == timer_count) {
			return false;
		}
		pre_time = timer_count;
		return true;
	}
	inline void MasterXHWND::ChangeTime() {
		static int sys_clock = SDL_GetTicks();
		if(timer_count < sys_clock) {
			timer_count++;
		}
		else
		if(timer_count > sys_clock)
		{
			timer_count = SDL_GetTicks();
		}

	}
	inline void MasterXHWND::SetTimeFlag() {
		time_flag = TimeChange();
	}
	inline bool MasterXHWND::SyncChange() {
		return true;
	}

	inline SDL_Font * CreateMasterFont(char* font_name,int size) {
		return SDL_InitFont(font_name);
	}
};


// left for backwards compatiblity
class MasterJoyStick {
public:

	bool JoyExisit() {
		return false;

	}
	bool SetupJoystick()  {
		return true;
	}
	bool JoyBackward() {
			return false;
	}

	bool JoyForward() {

		return false;
	}
	int JoyButtonDown() {

		return -1;
	}

};

struct ScreenObject
{
	MASTERSCREEN sub_screen;
	MasterXHWND* mxhwnd;
	
	inline void Init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}
	
	inline MASTERSCREEN getscreen()
	{
		return sub_screen;
	}
	
	inline void setscreen(MASTERSCREEN xscreen)
	{
		sub_screen = xscreen;
	}
};

class MasterGameObject 
{
public:
	virtual void load() = 0;
	virtual void update() = 0;
};

extern "C" int SDL_main(int argc, char **argv) {

	// init sdl
	return MasterMain("");
}

#endif

