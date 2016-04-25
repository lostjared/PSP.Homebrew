#include "mxwnd.h"
#include "mx.h"
#include<string.h>




namespace mx
{

	static unsigned int __attribute__((aligned(16))) list[262144];
	u32 *base = (u32*) (0x40000000 | 0x04000000);



	mxDisplay::mxDisplay()
	{
		buffer_width=512;
		frame_size=512*272*4;
		flip = 0;
	}



	int exitCallback(int argi, int argz, void *ptr)
	{

		sceKernelExitGame();
		return 0;
	}



	int createExitThread(SceSize args, void *ptr)
	{

		int rt;
		rt = sceKernelCreateCallback("exit_call", exitCallback, 0);
		sceKernelRegisterExitCallback(rt);
		sceKernelSleepThreadCB();
		return 0;
	}


	int mxDisplay::initCallbacks()
	{

		int rt_val;
		rt_val = sceKernelCreateThread("update", createExitThread, 0x11, 0xFA0, 0, 0);
		if(rt_val >= 0)
			sceKernelStartThread(rt_val, 0, 0);

		return rt_val;

	}


	int mxDisplay::initDisplay()
	{
		sceGuInit();
		sceGuStart(GU_DIRECT, list);
		sceGuDrawBuffer(GU_PSM_8888, (void*)frame_size, buffer_width);
		sceGuDispBuffer(screen_width, screen_height, (void*) 0, buffer_width);
		sceGuDepthBuffer((void*)(frame_size*2), buffer_width);
		sceGuOffset(2048 - (screen_width/2), 2048 - (screen_height/2));
		sceGuViewport(2048, 2048, screen_width, screen_height);
		sceGuDepthRange(65535, 0);
		sceGuScissor(0,0,screen_width, screen_height);
		sceGuEnable(GU_SCISSOR_TEST);
		sceGuDepthFunc(GU_GEQUAL);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuFrontFace(GU_CW);
		sceGuShadeModel(GU_SMOOTH);
		sceGuEnable(GU_CULL_FACE);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuEnable(GU_CLIP_PLANES);
		sceGuFinish();
		sceGuSync(0,0);
	

		sceDisplayWaitVblankStart();
		sceGuDisplay(GU_TRUE);

		is_active = true;


		return 1;
	}

	mxDisplay::~mxDisplay()
	{
		sceGuTerm();
		sceKernelExitGame();
	}

	u32 *mxDisplay::drawBuffer()
	{
		u32 *frame = (u32*) base;
		if(flip == 0) frame += frame_size/sizeof(u32);
		return frame;
	}


	void mxDisplay::flipBuffer()
	{

		sceGuFinish();
		sceGuSync(0,0);



		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
		flip = !flip;

	}

	void mxDisplay::clearBuffer()
	{

		sceKernelDcacheWritebackInvalidateAll();
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);//(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
	}

	void mxDisplay::start()
	{
		sceGuStart(GU_DIRECT, list);
	}

	void mxDisplay::end()
	{

		sceGuFinish();
		sceGuSync(0,0);

	}

	void mxDisplay::setPixel(int x, int y, unsigned int color)
	{
		drawBuffer()[(buffer_width*y)+x] = color;
	}

	unsigned int mxDisplay::getPixel(int x, int y) 
	{

		return (drawBuffer()[(buffer_width*y)+x]);
	}

	void mxDisplay::copySurface(mxSurface *surf, int x, int y)
	{

		sceGuCopyImage(GU_PSM_8888, 0, 0, screen_width, screen_height, surf->tw,  surf->data, x, y, buffer_width, drawBuffer());

	}

	int mxDisplay::printText(mxFontObject *fnt, int x, int y, unsigned int color, char *text)
	{
		int prev_x = x;
		int offset_x = prev_x, offset_y = y;
		int width_x = 0, height_x = 0;
		int i,z,p;

		if(fnt->font == 0) return -1;

		for(p = 0; p < (int)strlen(text);  p++) {
		if(text[p] == '\n') {
			offset_x = prev_x;
			offset_y += height_x;
			continue;
		}
		for(i = 0; i < fnt->font->mx; i++) {
			for(z = 0; z < fnt->font->my; z++) {
				if(fnt->font->letters[(int)text[p]].fnt_ptr[i][z] != fnt->font->tcolor) {
					if(offset_y+z > 0 && offset_x+i > 0 && offset_y+z < screen_height && offset_x+i < screen_width)
					setPixel(offset_x+i, offset_y+z, color);


					width_x=i;


					if(height_x < z)
						height_x=z;
				}
			}
		}

		offset_x += width_x + 3;
		if(offset_x+width_x >= screen_width) {
			offset_x = prev_x;
			offset_y += height_x;
		}
		if(offset_y+height_x > screen_height)
				return 1;
					
		}


		return 0;
		
	}


}

