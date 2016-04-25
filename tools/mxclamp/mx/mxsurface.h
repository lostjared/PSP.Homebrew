#ifndef __MX_SURFACE__H__
#define __MX_SURFACE__H__

#include "SDL.h"
#include<iostream>


namespace mx
{

	using std::cout;


	class mxSurface {

	public:
		mxSurface(SDL_Surface *surface = 0);
		mxSurface(const mxSurface &c);
		virtual ~mxSurface();

		mxSurface& operator=(const mxSurface &c);
		mxSurface& operator=(SDL_Surface *surface);
		SDL_Surface *getSurface() const;
		operator SDL_Surface *();

		bool copySurface(const mxSurface &c, SDL_Rect *source, SDL_Rect *dest);
		bool copySurfaceColorKey(const mxSurface &c, SDL_Rect *source, SDL_Rect *dest, SDL_Color color_key);
		void Flip();
		virtual void noZero(bool noremove);
		void cleanSurface();

	protected:
		SDL_Surface *object_surface;
		void clean_up();
	private:
		bool protected_noremove;


	};

}


#endif

