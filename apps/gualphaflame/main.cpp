#include<mx.h>
#include <pspkerneltypes.h>	//# |_ For 333Mhz Overclock
#include <psppower.h>		//# |
#include<sstream>

#define SCR_WIDTH 480
#define SCR_HEIGHT 272

// module information

PSP_MODULE_INFO("mxpsp_gualpha", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

// instances of class mxSurface

mx::mxSurface images[4];
mx::mxSurface back_surface;


// usefull typedef for RGBA color

typedef union _Color {

	unsigned char c[4];
	unsigned int color;

} Color;
	

// function prototypes
void loadSurfaces();
void scrambleSurface();
void blendSurface(mx::mxSurface *surface);
void morphSurface();


// pointer to the controller object
mx::mxController *control;


//main function
int main(int argc, char **argv)
{

	mx::mxDisplay display; // display instance
	mx::mxController controller;
	

	if(display.initCallbacks() && display.initDisplay())
	{

		scePowerSetClockFrequency(333, 333, 166);

		loadSurfaces();
		scrambleSurface();


		while(display.active())
		{


			display.clearBuffer();

			morphSurface();
			blendSurface(&images[rand()%4]);

			display.end();


			display.start();


			display.copySurface(&back_surface, 0, 0);

			display.flipBuffer();
		}


	}


	return 0;
}



void loadSurfaces()
{

	for(int i = 0; i < 4; i++)
	{
		std::ostringstream stream;
		stream << "img/surface" << (i+1) << ".bmp";
		images[i].loadImage(stream.str().c_str());
	}

	back_surface.createSurface(480,272);

}

void scrambleSurface()
{


	for(int i = 0; i < SCR_WIDTH; i++)
	{
		for(int z = 0; z < SCR_HEIGHT; z++)
		{

			Color col, final_color;

			col.color = images[rand()%4].getPixel(i,z);
			final_color.c[0] = col.c[0];
			col.color = images[rand()%4].getPixel(i,z);
			final_color.c[1] = col.c[1];
			col.color = images[rand()%4].getPixel(i,z);
			final_color.c[2] = col.c[2];
			final_color.c[3] = 0;
			back_surface.setPixel(i,z,final_color.color);

		}

	}


}

void blendSurface(mx::mxSurface *surface)
{
	int i,z;
	static float alpha = 1.0f;


	for(i = 0; i < SCR_WIDTH; i++)
	{
		for(z = 0; z < SCR_HEIGHT; z++)
		{

			Color color1, color2, color3;


			color1.color = surface->getPixel(i,z);
			color2.color = back_surface.getPixel(i,z);
			 
			color3.c[0] = static_cast<unsigned char>( color2.c[0] + (alpha*color1.c[0]) );
			color3.c[1] = static_cast<unsigned char>( color2.c[1] + (alpha*color1.c[1]) );
			color3.c[2] = static_cast<unsigned char>( color2.c[2] + (alpha*color1.c[2]) );

			back_surface.setPixel(i,z,color3.color);

		}

	}

}

void morphSurface()
{
	int i,z;
	for(i = 0; i < SCR_WIDTH-41; i++)
	{
		for(z = 0; z < SCR_HEIGHT-1; z++)
		{
			unsigned int col[3];
			Color colorz[4];

			colorz[0].color = back_surface.getPixel(i,z);
			colorz[1].color = back_surface.getPixel(i+1,z);
			colorz[2].color = back_surface.getPixel(i, z+1);
			colorz[3].color = back_surface.getPixel(i+1, z+1);

			col[0] = colorz[0].c[0] + colorz[1].c[0] + colorz[2].c[0] + colorz[3].c[0];
			col[1] = colorz[0].c[1] + colorz[1].c[1] + colorz[2].c[1] + colorz[3].c[1];
			col[2] = colorz[0].c[2] + colorz[2].c[2] + colorz[2].c[2] + colorz[3].c[2];

			col[0] /= 4;
			col[1] /= 4;
			col[2] /= 4;

			Color set_color;
			set_color.c[0] = static_cast<unsigned char>(col[0]);
			set_color.c[1] = static_cast<unsigned char>(col[1]);
			set_color.c[2] = static_cast<unsigned char>(col[2]);
			set_color.c[3] = 0;

			back_surface.setPixel(i,z, set_color.color);


		}

	}


}







