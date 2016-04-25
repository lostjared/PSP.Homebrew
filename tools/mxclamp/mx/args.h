#ifndef __ARGS__H_
#define __ARGS__H_

#include<string>
#include<vector>
#include<iostream>

namespace mx
{

	using std::string;


	class mxArgs {

	public:

		explicit mxArgs(int &argc, char **argv);
		bool testForSwitchAndRemove(string what);
		bool testForSwitchAndLeave(string what);
		string testForItem(string what);



	protected:
		std::vector<std::string> arglist;


	};






}










#endif

