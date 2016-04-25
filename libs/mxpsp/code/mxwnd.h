#ifndef _MXPSP_WND_H_
#define _MXPSP_WND_H_

namespace mx
{


	class mxSurface;
	class mxFontObject;

	class mxDisplay {

	protected:
		int buffer_width;
		int frame_size;
		unsigned int flip;
		bool is_active;

	public:

		enum { screen_width = 480,

		 	screen_height = 272 };
	

		mxDisplay();
		~mxDisplay();
		int initCallbacks();
		int initDisplay();
		unsigned int *drawBuffer();
		void clearBuffer();
		void flipBuffer();
		void copySurface(mxSurface *surf, int x, int y);

		int printText(mxFontObject *font, int x, int y, unsigned int color, char *text);

		void start();
		void end();

		void setPixel(int x, int y, unsigned int color);
		unsigned int getPixel(int x, int y);

		const bool active() const { return is_active; }
		void exit() { is_active = false; } 
		

	};


	

}




#endif

