
#include "cross_gta.h"
#ifdef FOR_PSP
#include "utils.c"
#include "cross_gta.c"
#endif


void render() {

	draw_text(font_array,font_w,font_h,10,10,map_rgb(rand()%255,rand()%255,rand()%255), "Hello World!");
}

void joy_button(int b) {


}

void Main(void) {

	init_app();
	loop(render,joy_button);
	clean_app();

}