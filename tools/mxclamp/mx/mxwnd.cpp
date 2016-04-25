#include "mxwnd.h"



namespace mx
{



	mxWnd::mxWnd(int w, int h, Uint32 flags, bool opengl_init)
	{

		active = false;

		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
			throw mxException<string>("could not initalize SDL");


		const SDL_VideoInfo *vi = SDL_GetVideoInfo();

		if(vi == 0)
			throw mx::mxException<std::string>(" could not get information on video ");

		Uint8 bpp=0;
		
		bpp = vi->vfmt->BitsPerPixel;

		if(vi->hw_available)
			flags |= SDL_HWSURFACE;
		else flags |= SDL_SWSURFACE;

		if(vi->blit_hw)
			flags = SDL_HWACCEL;


		if(opengl_init == true)
		{
			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		}



		front = SDL_SetVideoMode(w,h,bpp,flags);

		vid_flags = flags;
		
		front.noZero(true); // no zero here , because the surface is freed by the call to SDL Quit

		std::cout << "SDL: subsystem initalized\n";

	}

	mxWnd::~mxWnd()
	{

		SDL_Quit();
		std::cout << "SDL: subsystem shutdown\n";
	
	}


	int mxWnd::messageLoop()
	{

		static SDL_Event e;

		active = true;


		while(active == true)
		{

			while(SDL_PollEvent(&e))
			{

				eventPassed(e);

			}

			renderScreen();

		}

		return EXIT_SUCCESS;
	}

	void mxWnd::quit()
	{
		active = false;
	}


	void mxWnd::eventPassed(SDL_Event &e)
	{
		if(e.type == SDL_QUIT) active = false;
		else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) active = false;
	}



	void mxWnd::renderScreen()
	{

		SDL_FillRect(front, 0, SDL_MapRGB(front.getSurface()->format, 255, 255, 255));
		front.Flip();

	}

	void mxWnd::setTitle(string title)
	{

		SDL_WM_SetCaption(title.c_str(), 0);

	}


}



