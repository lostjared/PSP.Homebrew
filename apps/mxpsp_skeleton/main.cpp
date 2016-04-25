#include<mx.h>

PSP_MODULE_INFO("mxpsp_skeleton", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);




int main(int argc, char **argv)
{

	mx::mxDisplay d;
	mx::mxController controller;


	if(d.initCallbacks() && d.initDisplay())
	{

		while( d.active() )
		{

			d.clearBuffer();

			for(int i = 0; i < 480; i++)
			{
				for(int z = 0; z < 272; z++)
				{

					d.setPixel(i,z, rand()%0xFFFFFF);

				}

			}


			d.flipBuffer();


			if(controller.pollNum( mx::MX_CROSS) )
				d.exit();

		}

	}

	return 0;
}


