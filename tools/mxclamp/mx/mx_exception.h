#ifndef __MXE__H__
#define __MXE__H__

#include <iostream>
#include <string>


namespace mx
{



	using std::ostream;
	using std::string;


	template<typename Type> 
	class mxException {

	public:
		explicit mxException(Type t)
		{
			data = t;
		}

		const void printError(ostream &out) const
		{

			out << data << "\n";
		}

	protected:
		Type data;

	
	};

}


#endif
