#ifndef __INTERFACE__H__
#define __INTERFACE__H__
extern "C"
{
#include "SDL_mxf.h"
}


#include "mxsurface.h"
#include "mx_types.h"
#include "mx_exception.h"



namespace mx
{

	class mxSurfacePainter {

	public:

		mxSurfacePainter(mxSurface *surface = 0);
		void resetSurface(mxSurface *surface);
	  	const bool paintLock();
		const bool paintUnlock();
		const bool setPixel(int x, int y, Color col);
		const bool setPixel(int x, int y, Uint32 color);

		const bool getPixel(int x, int y, SDL_Color *col, Color &return_col);
		const Uint32 getPixel(int x, int y, SDL_Color *col); // for 24-bit
		
		void setFont(SDL_Font *font) { this->font = font; }
		void printText(int x, int y, Color col,std::string text);
		
	private:
		mxSurface *surface;
		void      *pbuf;
		bool locked;
		SDL_Font *font;

	};



}














#endif

