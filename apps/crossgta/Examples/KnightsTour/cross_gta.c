
int GetFX(int mx,int x, int nw) {
	float xp = (float)x * (float)mx / (float)nw;		
	return (int)xp;
}

int GetFZ(int my, int y, int nh) {
	float yp = (float)y * (float)my / (float)nh;
	return (int)yp;
}


void init_app() {
	initScreenAndCtrl();
	fill_rect(0,0,480,272,0x0);
	changeBuffer();
}

void loop(void (*renderx)(),void (*joy_down)(int button)) {
	int i = 0;
	while(1) {
		fill_rect(0,0,480,272, 0x0);
		renderx();
		swap_buffer();
		// proccess joybutton down
		
		if(i % 6 == 0) {
		sceCtrlReadBufferPositive(&gpaddata,1);
		WriteDwordDummy(0,22,gpaddata.Buttons);

			 if(gpaddata.Buttons & PSP_CTRL_CROSS)
			 {
				 joy_down(0);
			 }
			 if(gpaddata.Buttons & PSP_CTRL_CIRCLE) {
				 joy_down(1);
			 }
		}

		i++;
	}
}

void swap_buffer() {

	changeBuffer();

}
// no bounds checking
void set_pixel(int x, int y, unsigned long color) {
	unsigned long *vptrc = 0, *vptrl = 0;
		vptrc = (unsigned long*)GetVramAddr(x,y);
		vptrl = (unsigned long*)vptrc;
		*vptrl =(unsigned long) color;
}
void clean_app() { 
// left empty since you cant exit the application 

}

int draw_text(unsigned int *fnt_ptr,int font_w, int font_h,  int x, int y, unsigned long color, char *src) {
	int prev_x = x;
	int offset_x = prev_x, offset_y = y;
	int width = 0, height = 0;
	int i,z,p;

	for(p = 0; p < (int)strlen(src);  p++) {
		unsigned int *ptr = fnt_ptr;
		if(src[p] == '\n') {
			offset_x = prev_x;
			offset_y += height;
			continue;
		}
		
		ptr += (src[p] * (font_w*font_h));
			
		for(i = 0; i < font_w; i++) {
			for(z = 0; z < font_h; z++) {
			
				if((*ptr)) {
					if(offset_y+z > 0 && offset_x+i > 0 && offset_y+z < 272 && offset_x+i < 480)
					set_pixel(offset_x+i, offset_y+z, color);
					width=i;
					if(height < z)
						height=z;
				}
				ptr++;
			}
		}
		offset_x += width;
		if(offset_x+width >= 480) {
			offset_x = prev_x;
			offset_y += height;
		}
		if(offset_y+height > 272)
				return 1;
					
	}

	return 0;
}
void fill_rect(int x, int y, int w, int h, unsigned long color) {
	RECT rc;
	rc.left = x;
	rc.right = w;
	rc.top = y;
	rc.bottom = h;
	FillRect(&rc, color);
}
void draw_bitmap(unsigned long *raw_bits,  int x, int y, int w, int h, int orig_w, int orig_h, unsigned long ckey) {
	int i,z;

	for(i = 0; i < w; i++)
		for(z = h; z > 0; z--) {
			int pos_x = GetFX(orig_w,i,w);
			int pos_y = GetFZ(orig_h,z,h);
			if(raw_bits[pos_x+pos_y*w] != ckey)
			set_pixel(i+x,z+y, raw_bits[pos_x+pos_y*w]);
		}
}
unsigned long map_rgb(unsigned char r, unsigned char g, unsigned char b) {
	return 0xFF;
}
