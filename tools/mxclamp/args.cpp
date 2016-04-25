#include "args.h"



namespace mx
{


	mxArgs::mxArgs(int &argc, char **argv)
	{


		try
		{

			int i;
			for(i = 1; i < argc; i++)
			{
				arglist.push_back(argv[i]);
			}

		}
		catch (std::bad_alloc &bad)
		{

			std::cerr << "error allocating memory\n";

		}
		catch (...)
		{
			std::cerr << "error unknown exception\n";
		}
	}


	bool mxArgs::testForSwitchAndRemove(string what)
	{

		std::vector<std::string>::iterator i;
		for(i = arglist.begin(); i!=arglist.end(); i++)
		{
			if(what == *i)
			{
				arglist.erase(i);
				return true;
			}

		}
		return false;
	}

	bool mxArgs::testForSwitchAndLeave(string what)
	{

		std::vector<std::string>::iterator i;
		for(i = arglist.begin(); i!=arglist.end(); i++)
		{
			if(what == *i)
				return true;
		}
		return false;
	}

	string mxArgs::testForItem(string what)
	{
		std::vector<std::string>::iterator i;

		for(i = arglist.begin(); i!=arglist.end(); i++)
		{
			int position = 0;
			std::string temp = *i;
			position = i->find("=");

			if(position != -1)
			temp = i->substr(0, position );
			

			if(what == temp)
			{

				if(position == -1) 
				{

					if(i+1 != arglist.end())
					{
						std::vector<std::string>::iterator z = i+1;
						if(z->at(0) != '-')
							return *z;
					}
				}
				else
				{

					std::string leftOf = i->substr(position+1, i->length()-position );
					return leftOf;
				}

			}

		}

		return string("");

	}



}




