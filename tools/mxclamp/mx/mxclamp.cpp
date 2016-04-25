#include "mxclamp.h"




namespace mx
{


	mxClampOutFile::mxClampOutFile(string filename)
	{
		fname = filename;
	}

	mxClampOutFile::~mxClampOutFile()
	{

		if(file.is_open())
		file.close();

	}


	bool mxClampOutFile::openFile()
	{

		file.open(fname.c_str(), std::ios::out | std::ios::binary);
		if(!file.is_open())
			return false;

		return true;
	}



	/* writes files to be compressed to disk
		if compression files throws mxException */

	bool mxClampOutFile::writeToFile()
	{

		vector<mxClamp_info>::iterator vi;
		vector<string>::iterator si;


		for(vi = files.begin(), si = file_names.begin(); vi != files.end(); vi++, si++)
		{
			uLongf size_compressed = vi->size_bytes;
			fstream ifile;
			void *temp, *tempc;
			temp = (void*) malloc ( sizeof(char) * vi->size_bytes+1 );
			tempc = (void*) malloc ( sizeof(char) * vi->size_bytes+1 );
			ifile.open(si->c_str(), std::ios::in | std::ios::binary);
			ifile.read((char*)temp, vi->size_bytes);
			ifile.close();
			if(compress((Bytef*)tempc, (uLongf*)&size_compressed, (const Bytef*) temp, (uLong) vi->size_bytes) != Z_OK)
			{


				throw mx::mxException<string>(" compression error ");			


			}
			cout << "file " <<  *si << " before compression " << vi->size_bytes << " after " << size_compressed << "\n";
			vi->size_compressed = size_compressed;
			file.write((char*)&*vi, sizeof(mxClamp_info));
			file.write((char*)tempc, vi->size_compressed);
			free(temp);
			free(tempc);
			
		}


		file.close();

		return true;
	}


	/* adds a file to the list of files to be written
		if file is not found throws mxException */

	bool mxClampOutFile::addFile(string name)
	{

		if(name.length()==0) return false;


		fstream testfile;
		testfile.open(name.c_str(), std::ios::in);
		if(!testfile.is_open())
			throw mx::mxException<std::string>(" Error file " + name + " not found cannot add to file list ");
		
		testfile.seekg(0, std::ios::end);
		mxClamp_info info;

		info.size_bytes = testfile.tellg();

		testfile.close();

		string pless;
		int pos = 0;

		pos = name.rfind("/");
		if(pos != -1)
		{

			pless = name.substr(pos+1, name.length()-pos);


		} else pless = name;
		snprintf(info.filename, 255, "%s", pless.c_str());

		files.push_back(info);
		file_names.push_back(name);
		return true;
	}


	/* attempts to open the file if fails throws mxException */

	mxClampResourceFile::mxClampResourceFile(string filename)
	{


		fname = filename;

		the_file.open(filename.c_str(), std::ios::in | std::ios::binary);
		if(!the_file.is_open())
			throw mx::mxException<string>(" error could not open .mxd resource file ");


		buildInfo();



	}

	mxClampResourceFile::~mxClampResourceFile()
	{

		if(the_file.is_open())
			the_file.close();

	}

	void mxClampResourceFile::reopen()
	{

		return ; // blah

		the_file.close();

		the_file.open(fname.c_str(), std::ios::in | std::ios::binary );
		if(!the_file.is_open())
			throw mx::mxException<string> (" Could not reopen .mxd archive \n");

		the_file.seekg(0, std::ios::beg);

	}


	void mxClampResourceFile::buildInfo()
	{

		mxClamp_info i;
		std::cout << "building information about compressed .mxd archive ...\n";


		while(!the_file.eof())
		{

			int position;

			memset(&i, 0, sizeof(i));

			the_file.read((char*)&i, sizeof(i));

			position = the_file.tellg();
	
			if(position == -1) break;
			
			std::cout << "read " << i.filename <<  "(" << i.size_compressed << " / " << i.size_bytes << ")" << " from compressed archive \n";
			file_names.push_back(i);
			clamp_off.push_back(position);
			
			the_file.seekg(i.size_compressed, std::ios::cur);
			
		}

		the_file.close();		

	}


	/* operator [] throws a exception when a filename that is not within the archive is quiered
		access raw bytes returns zero instead */


	void *mxClampResourceFile::operator[](string filename)
	{
		unsigned int s;
		void *bytes = accessRawBytes(filename, s);
		if(bytes == 0)
			throw mxException<string>(" Invalid file name, does not exisit within archive ");
		
		return bytes;


	}
	

	void *mxClampResourceFile::accessRawBytes(string filename, unsigned int &size)
	{

		vector<mxClamp_info>::iterator i;
		vector<unsigned int>::iterator ui;
		std::fstream the_file;

		the_file.open(fname.c_str(), std::ios::in | std::ios::binary);

		if(!the_file.is_open()) { return 0; }

		the_file.seekg(0, std::ios::beg);


		for(i=file_names.begin(),ui=clamp_off.begin(); i!=file_names.end(); i++, ui++)
		{
			
			if(i->filename == filename)
			{

				uLongf ulen = i->size_bytes;
				the_file.seekg(*ui, std::ios::beg);
				void *ctemp, *temp;
				ctemp = (void*) malloc ( i->size_compressed + 1 );
				temp = (void *) malloc ( i->size_bytes + 1 );
				the_file.read((char*)ctemp, i->size_compressed );

				

				if(uncompress((Bytef*)temp, &ulen,(const Bytef*)ctemp, (uLongf)i->size_compressed) == Z_DATA_ERROR)
				{
					the_file.close();
					throw mx::mxException<string>(" error on decompression of file " + string(filename));

				}
				free(ctemp);

				std::cout << "successfully accessed " << filename << "\n";
				size = i->size_bytes;
				the_file.close();
				return temp;
			}

		}

		the_file.close();
		return 0;
	}


}

