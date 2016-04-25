
#ifndef _MX_H_
#define _MX_H_

#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>

void *lock(SDL_Surface *surf, Uint8 type) {
	if(SDL_MUSTLOCK(surf)) {
		if(SDL_LockSurface(surf) < 0)
			return 0;
	}

	type = surf->format->BitsPerPixel;

	switch(surf->format->BitsPerPixel) {
		case 1:
		case 8:
			return (Uint8*)surf->pixels;
			break;
		case 16:
		case 2:
			return (Uint16*)surf->pixels;
			break;
		case 24:
		case 3:
			return (Uint32*)surf->pixels;
			break;
		case 32:
		case 4:
			return (Uint32*)surf->pixels;
			break;
		default:
			break;
	}

	return 0;

}



void unlock(SDL_Surface *surf) {
	if(SDL_MUSTLOCK(surf)) {
		SDL_UnlockSurface(surf);
	}
}

void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 type, Uint16 pitch) {
	static Uint8 *ubuff8 = 0;

	switch(type) {
		case 1:
		case 8:
			{ 
				Uint8 *buf = (Uint8*)buff;
				buf += (y * pitch) + x;
				*buf = (Uint8) color;

			}
			break;
		case 2:
		case 16:
			{
				static Uint16 *ubuff16 = 0;
				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*2);
				
				ubuff16 = (Uint16*) ubuff8;
				*ubuff16 = (Uint16) color;
			}
			break;
		case 3:
		case 24:
			{
				static char c1 = 0,c2 = 0,c3 = 0;

				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*3);
				if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
					c1 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c3 = (color & 0x0000FF);
				} else {
					c3 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c1 = (color & 0x0000FF);
				}
				ubuff8[0] = c3;
				ubuff8[1] = c2;
				ubuff8[2] = c1;
			}
			break;
		case 4:
		case 32:
			{
			static Uint32 *ubuff32 = 0;
			ubuff8 = (Uint8*) buff;
			ubuff8 += (y*pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			}
			break;
	}

}

Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 type, Uint16 pitch) {
	static Uint8 *bitz = 0;
	Uint32 bpp = (Uint32) type;
	bitz = ((Uint8 *)surf->pixels)+y*pitch+x*(bpp/8);
	switch(type) {
		case 8:
		case 1:
			return *((Uint8 *)surf->pixels + y * pitch + x);
			break;
		case 16:
		case 2:
			return *((Uint16 *)surf->pixels + y * pitch/2 + x);
			break;
		case 3:
		case 24:
			{
				Uint8 r, g, b;
				r = *((bitz)+surf->format->Rshift/8);
				g = *((bitz)+surf->format->Gshift/8);
				b = *((bitz)+surf->format->Bshift/8);
				return SDL_MapRGB(surf->format,r,g,b);
			
			}
		case 32:
		case 4:
			return *((Uint32 *)surf->pixels + y * pitch/4 + x);
			break;
	}

	return 0;
}


// wrapper class
class mxHwnd {

	void (*renderscr)(int screen);
	void (*keyfunc)(int key);
	void (*keyfuncup)(int key);
	void (*mousemove)(int x, int y);
	void (*mousedown)(int button, int x, int y);
	void (*onevent)(SDL_Event *ievent);

	int scr,exitok;
	int is_fullscreen;
	

public:

	void *buf;
	SDL_Surface *pscr;

	int setfullscreen(int fullscreen,char *title, int width, int height, int bpp)
	{
		SDL_FreeSurface(pscr);
		pscr = SDL_SetVideoMode(width, height, 0, 0);
		if(!pscr)
		{
			fprintf(stderr, "Couldn't create a surface: %s\n",SDL_GetError());
			return -1;
		}
		//SDL_WM_SetCaption(title, NULL);
		printf("Successfully initalized\n");
		scr = 0;
		is_fullscreen = fullscreen;
		return 0;
	}

	int isFullScreen() const
	{
		return is_fullscreen;
	}

	int init(char *title, int width, int height, int bpp, bool fullscreen)
	{
		if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 )
		{
			fprintf(stderr, "Could not initialize SDL: %s\n",SDL_GetError());
			return -1;
		}
		atexit(SDL_Quit);
		pscr = SDL_SetVideoMode(width, height, 0, 0);
		
		if(!pscr)
		{
			fprintf(stderr, "Couldn't create a surface: %s\n",SDL_GetError());
			return -1;
		}
		SDL_WM_SetCaption(title, NULL);
		printf("Successfully initalized\n");
		scr = 0;

		keyfunc = 0,keyfuncup = 0,mousemove = 0,mousedown = 0,onevent = 0,exitok = 1;
		is_fullscreen = (int)fullscreen;

		return 0;
	}

	void setKeydown(void(*keyfuncx)(int key))
	{
		keyfunc = keyfuncx;
	}

	int getScreen() { return scr; }
	void setScreen(int scr) { this->scr = scr; }

	void setKeyup(void(*keyfuncupx)(int key))
	{
		keyfuncup = keyfuncupx;
	}

	void setMouseMove(void (*mousemovex)(int x, int y))
	{
		mousemove = mousemovex;
	}

	void setMouseDown(void(*mousedownx)(int button, int x, int y))
	{
		mousedown = mousedownx;
	}

	void setEventHandler(void (*oneventx)(SDL_Event *ievent))
	{
		onevent = oneventx;
	}

	void clear()
	{
		SDL_Rect rect = {0, 0, pscr->w, pscr->h};
		SDL_FillRect(pscr, &rect, 0);
	}

	int initLoop(void (*rendery)(int screen))
	{
		renderscr = rendery;
		SDL_Event event;

		while(exitok == 1)
		{
			clear();
			renderscr(scr);
			while(SDL_PollEvent(&event))
			{
				switch( event.type )
				{
				case SDL_QUIT:
					printf("Quit called!\n");
					exitok = 0;
					break;
				/*case SDL_KEYDOWN:
					if(keyfunc != 0)
					{
						keyfunc(event.key.keysym.sym);
					}
					break;
				case SDL_KEYUP:
					if(keyfuncup != 0)
					{
						keyfuncup(event.key.keysym.sym);
					}
					break;*/
				}
				if(onevent != 0)
					onevent(&event);
			}
		}

		SDL_FreeSurface(pscr);
		SDL_Quit();

		return 1;
	}

	void kill()
	{
		exitok = 0;
	}

	void setPixel(SDL_Surface *screen, unsigned int x, unsigned int y, Uint8 r, Uint8 g, Uint8 b)
	{
		setpixel(buf, x,y,SDL_MapRGB(pscr->format, r, g, b ), pscr->format->BitsPerPixel, pscr->pitch);
				
	}

	void setPixel(SDL_Surface *screen, int x, int y, Uint32 color)
	{
		setpixel(buf, x,y,color, pscr->format->BitsPerPixel, pscr->pitch);
	}
	Uint32 getPixel(SDL_Surface *screen, int x, int y) {
		return getpixel(screen, x, y, pscr->format->BitsPerPixel, pscr->pitch);
	}
};

// base class for objects
class mxObject {

public:
	void init(mxHwnd *mx)
	{
		this->mx = mx;
	}
	mxHwnd *mx;
};

// Wrapper around SDL_Surface for bitmaps
class mxSprite : public mxObject {

public:
	SDL_Surface *sptr;

	mxSprite()
	{
		sptr = 0;
	}
	~mxSprite()
	{
		if(sptr != 0)
			SDL_FreeSurface(sptr);
		sptr = 0;
	}

	bool load(mxHwnd *mx, const char *str)
	{
		this->mx = mx;
		return load(str);
	}

	bool load(const char *str)
	{
		sptr = SDL_LoadBMP(str);
		if(sptr == 0)
		{
			fprintf(stderr, "Unable to load bitmap..%s\n",str);
			return false;
		}
		else 
			return true;
	}

	bool load(const char *str, int r, int g, int b)
	{
		sptr = SDL_LoadBMP(str);
		if(sptr == 0)
		{
			fprintf(stderr, "Unable to load bitmap ..%s", str);
			return false;
		}
		SDL_SetColorKey(sptr , SDL_SRCCOLORKEY,SDL_MapRGB(sptr->format, r,g,b));

		return true;
	}

	void display(class mxHwnd *mxhwnd, int x, int y, int x2, int y2, int w, int h)
	{
		SDL_Rect src;
		SDL_Rect dest;
		src.x = x2;
		src.y = y2;
		src.w = w;
		src.h = h;
		dest.x = x; dest.y = y;
		dest.w = h;
		dest.h = w;
		SDL_BlitSurface(sptr,&src,mxhwnd->pscr,&dest);
	}

	void display(class mxHwnd *mxhwnd, int x, int y)
	{
		display(mxhwnd,x,y,0,0,sptr->w,sptr->h);
	}

	// requires a call to init before use
	void display(int x, int y, int x2, int y2, int w, int h)
	{
		this->display(mx,x,y,x2,y2,w,h);
	}
	// same with this one
	void display(int x, int y)
	{
		this->display(mx,x,y);
	}

};



/*
// Wrapper around SFont
class mxFont : public mxObject {
public:
	SFont_Font* Font;

	mxFont()
	{
		Font = 0;
	}

	~mxFont()
	{
		if(Font != 0)
			SFont_FreeFont(Font);
	}

	void load(mxHwnd *mx, const char *sfont)
	{
		this->mx = mx;
		Font = SFont_InitFont(BMP_Load(sfont));
		if(!Font)
		{
			fprintf(stderr, "An error occured while loading the font.");
			exit(1);
		}

	}
	void printText(int x, int y, const char *str)
	{
		SFont_Write (mx->pscr, Font, x,y,str);
	}

};
*/

class mxPaint : public mxObject {

public:
	void drawRect(int x, int y, int x2, int y2, Uint32 color)
	{
		SDL_Rect rect = {x, y, x2, y2};
		SDL_FillRect(mx->pscr, &rect, color);
	}
};


class ArrayOf : public mxObject {
    Uint32 color;
    bool explo;
    void logic();
    public:
        ArrayOf();
        void render();
        void setDirection(int x, int y, int direction);      
        void setColor(Uint32 color);
        int x_pos, y_pos,direction,color_r,color_g,color_b;
        int which;
};

ArrayOf::ArrayOf()
{
    mx = 0;
    which = 0;
}    

void ArrayOf::setDirection(int x, int y, int direction)
{
    this->direction = direction;
    this->x_pos = x;
    this->y_pos = y;    
}


void ArrayOf::render()
{
    logic();
    if(mx != 0)
    if(which == 0)
     mx->setPixel(mx->pscr,x_pos,y_pos,color_r,color_g,color_b);
     else
     mx->setPixel(mx->pscr,x_pos,y_pos,color);
     
}   

void ArrayOf::logic()
{
   switch(direction)
   {
       case 0:
           x_pos += 2;
           y_pos -= 2;
       break;
       case 1:
                x_pos++;
                y_pos++;
                break;
       case 2:
                x_pos--;
                y_pos++;
                break;
       case 3:
                  y_pos--;
                  x_pos--;
                break;
                  case 4:
              x_pos++;
              y_pos--;
       break;
       case 5:
           y_pos--;
           explo = true;
           break;
           case 6:
               y_pos++;
               explo = true;
               break;
               
                       
     }
     
     static int wait = 0;
     if(explo == true && ++wait > 25)
     {
         direction = rand()%4;
         explo = false;  
         wait = 0;
     }                
                  
     if(x_pos <= 0 || y_pos <= 0 || x_pos >= 240 || y_pos >= 125)
     {
         setDirection(rand()%240,rand()%125,rand()%4);
         explo = false;
     }
                         
}

void ArrayOf::setColor(Uint32 color)
{
    this->color = color;   
    which = 1;
}


#endif
