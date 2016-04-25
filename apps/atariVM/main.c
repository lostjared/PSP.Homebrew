// The Atari Virtual Machine
// written by Jared Bruni
// of the one and only LostSideDead
// "Open Source, Open Mind"
// (-<) Peace


#include "masc.h"
#include "platform.h"
#include <SDL_mxf.h>


// ********************************** Begin System callbacks
void fill() {
	/*if(getfront())
	SDL_FillRect(getfront(), 0, 0);
	SDL_UpdateRect(getfront(), 0, 0, 480,272);*/
}

struct call_back calls[] = { {fill, 0x0}, {0, 0x0}};
int compile = 0;

// ********************************** End System callbacks

extern int SDL_main(int argc, char **argv) {

	struct file_buffer buffer;
	
	do_init();
	set_callback(calls);
	srand((unsigned int)time(0));
	
#ifndef FOR_PSP

	if(argc == 3 && strcmp(argv[2], "--debug") == 0)
		debug_mode = 1;
	else if(argc == 3 && strcmp(argv[2],"--debug=gfx") == 0)
		debug_mode = 2;
	
	


	if(argc == 2 || argc == 3)
	{
		mlex_init_file(&buffer,argv[1]);

		if(buffer.fptr != 0) {
			if(compile == 1) {
				mlex_anaylize(&buffer);
			} else
			mlex_anaylize(&buffer);
	
		}


		do_quit();
	}
	else {
		
		
		debug_mode = 0;
		mlex_init_file(&buffer,"default.ats");
		mlex_anaylize(&buffer);
		do_quit();
	}
#else
	    
	    mlex_init_file(&buffer,"default.ats");
		mlex_anaylize(&buffer);
		do_quit();
#endif
	return 0;
}