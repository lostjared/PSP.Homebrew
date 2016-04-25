#include "mxsurface.h"

namespace mx
{


	mxSurface::mxSurface(SDL_Surface *surface)
	{
		object_surface = surface;
		noZero(false);
	}

	mxSurface::mxSurface(const mxSurface &c)
	{
		clean_up();
		object_surface = c.object_surface;
		noZero(false);
	}


	mxSurface::~mxSurface()
	{
		clean_up();
	}


	mxSurface& mxSurface::operator=(const mxSurface &c)
	{
		clean_up();
		object_surface = c.object_surface;
		return *this;
	}

	mxSurface& mxSurface::operator=(SDL_Surface *surface)
	{
		clean_up();
		object_surface = surface;
		return *this;
	}

	SDL_Surface *mxSurface::getSurface() const
	{
		return object_surface;
	}

	bool mxSurface::copySurface(const mxSurface &c, SDL_Rect *source, SDL_Rect *dest)
	{

		if(object_surface == 0) return false;

		SDL_BlitSurface(c.object_surface, source, object_surface, dest);
		return true;

	}

	bool mxSurface::copySurfaceColorKey(const mxSurface &c, SDL_Rect *source, SDL_Rect *dest, SDL_Color color_key)
	{

		if(object_surface == 0) return false;

		SDL_SetColorKey(c.object_surface, SDL_SRCCOLORKEY, SDL_MapRGB(c.object_surface->format, color_key.r, color_key.g, color_key.b));
		copySurface(c, source, dest);

		return true;

	}

	void mxSurface::cleanSurface()
	{
		clean_up();
	}

	void mxSurface::clean_up()
	{
		if(object_surface && protected_noremove == false)
		{

			cout << "removing surface: " << int(object_surface) <<  " ";
			SDL_FreeSurface(object_surface);
			object_surface = 0;
			cout << "removed\n";
		}

	}

	void mxSurface::Flip()
	{
		SDL_Flip(object_surface);
	}

	mxSurface::operator SDL_Surface *()
	{
		return object_surface;
	}

	void mxSurface::noZero(bool zero)
	{
		protected_noremove = zero;
	}
}

