#include "mxcontroller.h"
#include "mx.h"




namespace mx
{





	int intTranslate(SceCtrlData *data)
	{
		if(data->Buttons & PSP_CTRL_SQUARE) return MX_SQUARE;
		if(data->Buttons & PSP_CTRL_TRIANGLE) return MX_TRIANGLE;
		if(data->Buttons & PSP_CTRL_CIRCLE) return MX_CIRCLE;
		if(data->Buttons & PSP_CTRL_CROSS) return MX_CROSS;
		if(data->Buttons & PSP_CTRL_START) return MX_START;
		if(data->Buttons & PSP_CTRL_SELECT) return MX_SELECT;
		if(data->Buttons & PSP_CTRL_LTRIGGER) return MX_LTRIGGER;
		if(data->Buttons & PSP_CTRL_RTRIGGER) return MX_RTRIGGER;
		if(data->Buttons & PSP_CTRL_LEFT) return MX_LEFT;
		if(data->Buttons & PSP_CTRL_RIGHT) return MX_RIGHT;
		if(data->Buttons & PSP_CTRL_UP) return MX_UP;
		if(data->Buttons & PSP_CTRL_DOWN) return MX_DOWN;

		return -1;
	}



	mxController::mxController()
	{
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	}


	bool mxController::getButtonDown(enum mxButton button)
	{

		SceCtrlData game_pad;

		sceCtrlReadBufferPositive(&game_pad, 1);


		if(game_pad.Buttons == 0) return false;
	
		if(button == intTranslate(&game_pad))
			return true;



		return false;
	}

	bool mxController::pollNum(int id)
	{

		SceCtrlData game_pad;
		sceCtrlReadBufferPositive(&game_pad, 1);
		if(game_pad.Buttons == 0) return false;
		if(game_pad.Buttons & id) return true;
		return false;
	}






}


