#include "mxinterface.h"

namespace mx
{

	mxSurfacePainter::mxSurfacePainter(mxSurface *surface)
	{
		this->surface = surface;
		pbuf = 0;
		locked = false;
		font = 0;
		
	}

	const bool mxSurfacePainter::paintLock()
	{

		pbuf = lock(this->surface->getSurface(), this->surface->getSurface()->format->BytesPerPixel);

		if(pbuf) locked = true;


		return true;

	}


	const bool mxSurfacePainter::paintUnlock()
	{
		unlock(this->surface->getSurface());

		locked = false;

		return true;
	}

	const bool mxSurfacePainter::getPixel(int x, int y, SDL_Color *col, Color &return_color)
	{


		if(locked == false) return false;

		


		return_color = getpixel(this->surface->getSurface(), x  , y ,   surface->getSurface()->format->BitsPerPixel, surface->getSurface()->pitch, col);

		return true;
	}
	
	const Uint32 mxSurfacePainter::getPixel(int x, int y, SDL_Color *col)
	{
		Uint32 rt_val = 0;

		rt_val = getpixel(surface->getSurface(), x, y, surface->getSurface()->format->BitsPerPixel, surface->getSurface()->pitch, col);


		return rt_val;
	}

	const bool mxSurfacePainter::setPixel(int x, int y, Color colz)
	{

		SDL_Color col = colz.toSDL_Color();


		if(locked == false) return false;


			setpixel(pbuf, x,y, SDL_MapRGB(this->surface->getSurface()->format, col.r, col.g, col.b), this->surface->getSurface()->format->BytesPerPixel, this->surface->getSurface()->pitch);

		return true;

	}


	const bool mxSurfacePainter::setPixel(int x, int y, Uint32 color)
	{
		if(locked == false) return false;

		setpixel(pbuf, x, y, color, surface->getSurface()->format->BytesPerPixel, surface->getSurface()->pitch);

		return true;

	}

	void mxSurfacePainter::resetSurface(mxSurface *surf)
	{
		surface = surf;
	}




	void mxSurfacePainter::printText(int x, int y, Color col,std::string text)
	{

		if(font == 0) throw mxException<string>(" No found font set on printtext [:" + text + ":]");

		SDL_PrintText(surface->getSurface(), font, x,y, SDL_MapRGB(surface->getSurface()->format, col.color.colors[0], col.color.colors[1], col.color.colors[2]), text.c_str());

	}










}








