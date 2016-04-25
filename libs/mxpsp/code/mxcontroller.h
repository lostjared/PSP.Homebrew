#ifndef MX_CONTROLLER_H__
#define MX_CONTROLLER_H__



namespace mx
{

	enum mxButton { 
		MX_CIRCLE = 0x002000, 
		MX_TRIANGLE = 0x001000, 
		MX_SQUARE = 0x008000 , 
		MX_CROSS = 0x004000, 
		MX_LEFT = 0x000080,
		MX_RIGHT = 0x000020, 
		MX_UP = 0x000010,
		MX_DOWN = 0x000040, 
		MX_START = 0x000008, 
		MX_SELECT = 0x000001,
		MX_LTRIGGER = 0x000100, 
		MX_RTRIGGER = 0x000200

	};




	class mxController {

	public:
		mxController();


		bool getButtonDown(enum mxButton button); // the method I use for this is quite inefficent outdated

		bool pollNum(int id); // you can use the ID 's in pspctrl.h with this function I guess


	};


}



#endif


