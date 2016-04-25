#ifndef __MX_TYPES_H__
#define __MX_TYPES_H__

#include<iostream>
#include<string>
#include "SDL.h"
#include "SDL_opengl.h"
extern "C"
{

#include "SDL_mxf.h"


}


#include "mx_exception.h"



namespace mx
{



	typedef union __Color
	{
		unsigned int  value;
		unsigned char colors[4];
	};


	class Color {

	public:
		Color();
		Color(unsigned char r, unsigned char g, unsigned char b);
		Color(const unsigned int value);
		Color(const Color &c);
		Color(const SDL_Color &c);

		Color& operator=(const Color &c);
		Color& operator=(const unsigned int long_x);
		Color& operator=(const SDL_Color &c);

		const unsigned int toInteger() const;
		const SDL_Color toSDL_Color() const;

		 __Color color;

	};

	

	


	
	
}






#endif


