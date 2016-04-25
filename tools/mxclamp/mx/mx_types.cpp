#include "mx_types.h"





namespace mx
{

 
	Color::Color()
	{

		color.value = 0;
	}


       Color::Color(unsigned char r, unsigned char g, unsigned char b)
	{

		color.colors[0] = r, color.colors[1] = g, color.colors[2] = b;
	}

	
	Color::Color(const unsigned int value)
	{
		color.value = value;
	}


	Color::Color(const Color &c)
	{
		color = c.color;
	}

	Color::Color(const SDL_Color &c)
	{

		color.colors[0] = c.r;
		color.colors[1] = c.g;
		color.colors[2] = c.b;

	}
	
	Color &Color::operator=(const Color &c)
	{
		color = c.color;
		return *this;
	}

	Color &Color::operator=(const unsigned int long_x)
	{

		color.value = long_x;
		return *this;

	}
	Color &Color::operator=(const SDL_Color &c)
	{

		color.colors[0] = c.r;
		color.colors[1] = c.g;
		color.colors[2] = c.b;
		return *this;
	}

	const SDL_Color Color::toSDL_Color() const
	{

		SDL_Color col = { color.colors[0], color.colors[1], color.colors[2] };
		return col;

	}

	const unsigned int Color::toInteger() const
	{
		return color.value;
	}

}


