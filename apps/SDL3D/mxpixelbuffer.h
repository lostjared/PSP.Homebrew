#include <SDL.h>


extern SDL_Surface *front;
extern void *buf;
int max_clip_x = 0, max_clip_y = 0, min_clip_x = 0, min_clip_y = 0;
#define D3DCOLOR unsigned long



inline unsigned long D3DCOLOR_XRGB(unsigned char r, unsigned char g, unsigned char b) {
	return SDL_MapRGB(front->format, r, g, b);
}

void setpixel(void *buf, Uint32 x, Uint32 y, Uint32 color, Uint8 type, Uint16 pitch) ;

inline void fast_sp(int x, int y, unsigned long color) {
	setpixel(buf,int(x),int(y),color,front->format->BitsPerPixel,front->pitch);
}


inline void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

inline void Swap(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

void *lock(SDL_Surface *surf, Uint8 type) {
	if(SDL_MUSTLOCK(surf)) {
		if(SDL_LockSurface(surf) < 0)
			return 0;
	}

	type = surf->format->BitsPerPixel;

	switch(surf->format->BitsPerPixel) {
		case 1:
		case 8:
			return (Uint8*)surf->pixels;
			break;
		case 16:
		case 2:
			return (Uint16*)surf->pixels;
			break;
		case 24:
		case 3:
			return (Uint32*)surf->pixels;
			break;
		case 32:
		case 4:
			return (Uint32*)surf->pixels;
			break;
		default:
			break;
	}

	return 0;

}



void unlock(SDL_Surface *surf) {
	if(SDL_MUSTLOCK(surf)) {
		SDL_UnlockSurface(surf);
	}
}

void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 type, Uint16 pitch) {
	static Uint8 *ubuff8 = 0;

	if(!(x >= 0 && x < front->w && y >= 0 && y < front->h))
		return;

	switch(type) {
		case 1:
		case 8:
			{ 
				Uint8 *buf = (Uint8*)buff;
				buf += (y * pitch) + x;
				*buf = (Uint8) color;

			}
			break;
		case 2:
		case 16:
			{
				static Uint16 *ubuff16 = 0;
				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*2);
				
				ubuff16 = (Uint16*) ubuff8;
				*ubuff16 = (Uint16) color;
			}
			break;
		case 3:
		case 24:
			{
				static char c1 = 0,c2 = 0,c3 = 0;

				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*3);
				if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
					c1 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c3 = (color & 0x0000FF);
				} else {
					c3 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c1 = (color & 0x0000FF);
				}
				ubuff8[0] = c3;
				ubuff8[1] = c2;
				ubuff8[2] = c1;
			}
			break;
		case 4:
		case 32:
			{
			static Uint32 *ubuff32 = 0;
			ubuff8 = (Uint8*) buff;
			ubuff8 += (y*pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			}
			break;
	}

}

void drawhline(int x,int x2, int y, D3DCOLOR color) {
	for(int p = x; p <= x2; p++)
		fast_sp(p,y,color);
}



void drawline(int start_x, int start_y, int stop_x, int stop_y, unsigned long color) {

	//Lock(); assumes its locked
	
	int y_unit,x_unit;
	int ydiff = stop_y-start_y;
	if(ydiff<0)
	{
		ydiff = -ydiff;
		y_unit=-1;
	}
	else
	{
		y_unit =1;
	}
	int xdiff=stop_x-start_x;
	if(xdiff<0)
	{
		xdiff=-xdiff;
		x_unit = -1;
	}
	else
	{
		x_unit = 1;
	}
	
	int error_term=0;
	if(xdiff>ydiff)
	{
		int length=xdiff+1;
		for(int i = 0; i <length; i++)
		{
			//SetPixel(dc,start_x,start_y,color);
			//fast_sp(start_x,start_y,rect.Pitch,color);
			setpixel(buf, start_x, start_y, color, front->format->BitsPerPixel, front->pitch);
			start_x += x_unit;
			error_term+=ydiff;
			if(error_term>xdiff)
			{
				error_term-=xdiff;
				start_y+=y_unit;
			}
		}
	}
	else
	{
		int length = ydiff+1;
		for(int i = 0; i < length; i++)
		{
			//SetPixel(dc,start_x,start_y,color);
			//fast_sp(start_x,start_y,rect.Pitch,color);
			setpixel(buf, start_x, start_y, color, front->format->BitsPerPixel, front->pitch);
			start_y += y_unit;
			error_term+=xdiff;
			if(error_term>0)
			{
				error_term-=ydiff;
				start_x += x_unit;
			}
			
		}
	}
}

void drawtoptri(int x1, int y1,int x2, int y2, int x3, int y3, unsigned long color) {

	float dx_right,dx_left,xs,xe,height;  

	int temp_x,temp_y,right,left;

	if (x2 < x1) {
		temp_x = x2;
		x2     = x1;
		x1     = temp_x;
	}

	height = float(y3-y1);

	dx_left  = (x3-x1)/height;
	dx_right = (x3-x2)/height;

	xs = (float)x1;
	xe = (float)x2; 
	if (y1 < min_clip_y) {
		xs = xs+dx_left*(float)(-y1+min_clip_y);
		xe = xe+dx_right*(float)(-y1+min_clip_y);
		y1=min_clip_y;
	}

	if (y3>max_clip_y)
		y3=max_clip_y;

	if (x1>=min_clip_x && x1<=max_clip_x && x2>=min_clip_x && x2<=max_clip_x && x3>=min_clip_x && x3<=max_clip_x) {
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			drawhline(int(xs),int(xs+(int)xe-xs+1),temp_y,color);
			xs+=dx_left;
			xe+=dx_right;
		} 
	}
	else {
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			left  = (int)xs;
			right = (int)xe;
			xs+=dx_left;
			xe+=dx_right;
			if (left < min_clip_x) {
				left = min_clip_x;
				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x) {
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			drawhline((int)left,(int)left+(int)right-left+1,temp_y,color);
		} 
	}
}

void drawgentri(int x0, int y0, int x1, int y1, int x2, int y2, D3DCOLOR color) {

	if( y1 < y0 )
	{
		Swap(y1, y0);
		Swap(x1, x0);
	}
	if( y2 < y0 )
	{
		Swap(y2, y0);
		Swap(x2, x0);
	}

	if( y1 < y2 )
	{
		Swap(y2, y1);
		Swap(x2, x1);
	}


	float xl_edge = (float)x0; 
	float xr_edge = (float)x0;
	float dxldy;
	float dxrdy;
	float dxdy1 = (float)(x2-x0)/(y2-y0);
	float dxdy2 = (float)(x1-x0)/(y1-y0);
	if( dxdy1 < dxdy2 )
	{
		dxldy = dxdy1;
		dxrdy = dxdy2;
	}
	else
	{
		dxldy = dxdy2;
		dxrdy = dxdy1;
	}

	for(int y=y0; y<y2; y++)
	{
		for(int x=int(xl_edge); x<int(xr_edge); x++)
		{
			fast_sp(x, y, color);
		}

		xl_edge = xl_edge + dxldy;
		xr_edge = xr_edge + dxrdy;

	}

	if( dxdy1 < dxdy2 )
	{
		dxldy = (float)(x2-x1)/(y2-y1);
	}
	else
	{
		dxrdy = (float)(x2-x1)/(y2-y1);
	}
	for(int y=y2; y<y1; y++)
	{
		for(int x=int(xl_edge); x<int(xr_edge); x++)
		{
			fast_sp(x,y,color);
		}

		xl_edge = xl_edge + dxldy;
		xr_edge = xr_edge + dxrdy;
	}
}

void drawbottomtri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color) {
	float dx_right,dx_left,xs,xe,height;     
	int temp_x,temp_y,right,left;
	if (x3 < x2) {
		temp_x = x2;
		x2     = x3;
		x3     = temp_x;
	}
	height = float(y3-y1);
	dx_left  = (x2-x1)/height;
	dx_right = (x3-x1)/height;

	xs = (float)x1;
	xe = (float)x1;
	if (y1 < min_clip_y) {
		xs = xs+dx_left*(float)(-y1+min_clip_y);
		xe = xe+dx_right*(float)(-y1+min_clip_y);
		y1 = min_clip_y;
	}

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	if (x1>=min_clip_x && x1<=max_clip_x && x2>=min_clip_x && x2<=max_clip_x && x3>=min_clip_x && x3<=max_clip_x) {
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			drawhline(int(xs),(int)xs+(int(xe-xs+1)),temp_y,color);
			xs+=dx_left;
			xe+=dx_right;

		} 
	}
	else
	{
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			left  = (int)xs;
			right = (int)xe;
			xs+=dx_left;
			xe+=dx_right;

			if (left < min_clip_x){
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			drawhline(int(left),(int)left+(int(right-left+1)),temp_y,color);
		}
	}
}

void drawtri(int x1, int y1,int x2, int y2, int x3, int y3, D3DCOLOR color) {
	int temp_x,temp_y,new_x;

	if ((x1==x2 && x2==x3)  ||  (y1==y2 && y2==y3))
		return;

	if (y2<y1) {
		temp_x = x2;
		temp_y = y2;
		x2     = x1;
		y2     = y1;
		x1     = temp_x;
		y1     = temp_y;
	}

	if (y3<y1) {
		temp_x = x3;
		temp_y = y3;
		x3     = x1;
		y3     = y1;
		x1     = temp_x;
		y1     = temp_y;
	}

	if (y3<y2) {
		temp_x = x3;
		temp_y = y3;
		x3     = x2;
		y3     = y2;
		x2     = temp_x;
		y2     = temp_y;

	} 
	if ( y3<min_clip_y || y1>max_clip_y || (x1<min_clip_x && x2<min_clip_x && x3<min_clip_x) || (x1>max_clip_x && x2>max_clip_x && x3>max_clip_x) )
		return;


	if (y1==y2)  {
		drawtoptri(x1,y1,x2,y2,x3,y3,color);
	} 
	else
		if (y2==y3){
			drawbottomtri(x1,y1,x2,y2,x3,y3,color);
		} 
		else {
			new_x = x1 + (int)(0.5+(float)(y2-y1)*(float)(x3-x1)/(float)(y3-y1));
			drawbottomtri(x1,y1,new_x,y2,x2,y2,color);
			drawtoptri(x2,y2,new_x,y2,x3,y3,color);
		} 
}
