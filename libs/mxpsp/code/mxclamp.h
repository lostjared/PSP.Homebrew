#ifndef __MX__H__CLAMP__H_
#define __MX__H__CLAMP__H_


#include<zlib.h>
#include<fstream>
#include<vector>
#include<iostream>
#include<string>



namespace mx
{

	using std::fstream;
	using std::vector;
	using std::cout;
	using std::string;



	struct mxClamp_info {
		char filename[256];
		unsigned int size_bytes, size_compressed;
	};

	class mxClampOutFile {

	public:
		explicit mxClampOutFile(string filename);
		~mxClampOutFile();

		bool openFile();
		bool writeToFile();
		bool addFile(string filename);

	private:
		string fname;
		fstream file;
		vector<mxClamp_info> files;
		vector<string> file_names;

	};

	class mxClampResourceFile {

	public:
		explicit mxClampResourceFile(string filename);
		~mxClampResourceFile();

		// access the data via [] operator
		// remember you must free the data
		// after you use it!
		void *operator[](string filename);
		void *accessRawBytes(string filename, unsigned int &size);
		
		vector<mxClamp_info> file_names;
		
	private:

		void buildInfo();
		void reopen();
		vector<unsigned int> clamp_off;

		fstream the_file;
		string  fname;


	};



}



#endif

