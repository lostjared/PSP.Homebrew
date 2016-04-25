
#include "cross_gta.h"
#ifdef FOR_PSP
#include "utils.c"
#include "cross_gta.c"
#endif


void render() {

	static int i,z;
	for(i = 0; i < 480; i++)
		for(z = 0; z < 272; z++)
	set_pixel(i,z,map_rgb(rand()%255,rand()%255,rand()%255));

}

void joy_button(int b) {


}

void Main(void) {

	init_app();
	loop(render,joy_button);
	clean_app();

}