#include "mp_c.h"
void render() {

	draw_text(font_array, font_w, font_h, 10,10,0xFFFFFFFFL, "MPGTA\0");
	draw_text(font_array, font_w, font_h, 10,30,map_rgb(255,0,0), "Score:");
	draw_int(font_array, font_w, font_h, 70,30,0xFFFFFFFFL, score);
	draw_grid();
	proc_move();
}

void joy_button(int b) {

	switch(b) {
		case 0:
			shiftcolor(&gblock, 1);
			break;
		case 1:
			shiftcolor(&gblock, 0);
			break;
		case 7:
			move_left();
			break;
		case 9:
			move_right();
			break;
	}

}

void Main(void) {

	init_app();
	init_matrix();
	loop(render,joy_button);
	clean_app();

}