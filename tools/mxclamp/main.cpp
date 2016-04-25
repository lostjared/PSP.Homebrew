#include "mxclamp.h"
#include "args.h"
#include<sstream>




void concatFiles(std::string fileList, std::string output)
{

	std::fstream file;
	file.open(fileList.c_str(), std::ios::in);
	if(!file.is_open())
	{
		throw mx::mxException<std::string>(" Error could not open file list: " + fileList);
	}


	mx::mxClampOutFile clamped(output);

	while(!file.eof())
	{
		std::string line;
		std::getline(file, line);
		clamped.addFile(line);

	}

	clamped.openFile();
	clamped.writeToFile();

	std::cout << "Successfully wrote to file: " << output << "\n";

	file.close();

}


void extractFile(std::string ifile, std::string getfile)
{

	mx::mxClampResourceFile rez(ifile);
	std::fstream fname;
	unsigned int size = 0;
	void *bytes = rez.accessRawBytes(getfile, size);	
	fname.open(getfile.c_str(), std::ios::out | std::ios::binary);
	fname.write((char*)bytes, size);
	fname.close();
	free(bytes);
}


void extractAll(std::string ifile, std::string epath)
{

	mx::mxClampResourceFile rez(ifile);

	if(epath[epath.length()-2] == '/') epath = epath.substr(0, epath.length()-2);

	for(int i = 0; i < rez.file_names.size(); i++)
	{

		std::fstream fname;
		std::string  file_no;
		std::ostringstream ff;
		ff << epath << "/" << rez.file_names[i].filename;
		file_no = ff.str();
		std::cout << "extracting " << file_no << "\n";
		unsigned int size = 0;
		void *bytes = rez.accessRawBytes(rez.file_names[i].filename, size);
		fname.open(file_no.c_str(), std::ios::out | std::ios::binary);
		fname.write((char*)bytes, size);
		fname.close();
		free(bytes);
	}

}

int main(int argc, char **argv)
{

	using mx::mxArgs;

	try
	{

		mxArgs argz(argc, argv);
		std::string item_list, outfile;

		item_list = argz.testForItem("--clist");
		outfile = argz.testForItem("--outfile");
		if(item_list  != "" && outfile != "")
		{
			concatFiles(item_list, outfile);
			return EXIT_SUCCESS;
		}


		std::string infile, getfile;

		infile = argz.testForItem("--ifile");
		getfile = argz.testForItem("--efile");
		if(infile != "" && getfile != "")
		{
			extractFile(infile, getfile);
			return EXIT_SUCCESS;
		}

		infile = argz.testForItem("--efile");
		getfile = argz.testForItem("--epath");
	
		if(infile != "" && getfile != "")
		{
			extractAll(infile, getfile);
			return EXIT_SUCCESS;
		}


		std::cout << "mxclamp arguments:\ncompression:\n --clist=list_of_files --outfile=compressed.mxd\ndecompression:\n--ifile=compressed.mxd --efile=file_to_extract\nextract all:\n--efile=compressed.mxd --epath=/file/path\n";


		return EXIT_SUCCESS;

	}
	catch(mx::mxException<std::string> &e)
	{
		e.printError(std::cerr);
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << "\n";

	}
	catch(...)
	{
		std::cerr << " unhandled exception fatal aborting..\n";
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;

}

