#ifndef __MXWND__H__
#define __MXWND__H__

#include "mxsurface.h"
#include "mx_types.h"


namespace mx
{


	class mxWnd {

	public:
		mxWnd(int w=640, int h=480, Uint32 flags=0, bool opengl_init=false);
		virtual ~mxWnd();
		int messageLoop();	
		
		virtual void eventPassed(SDL_Event &e);
		virtual void renderScreen();
		void setTitle(string title);
		void quit();

	protected:
		mxSurface front;
		bool active;
		Uint32 vid_flags;

	};

}










#endif


