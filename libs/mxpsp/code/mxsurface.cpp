#include "mxsurface.h"
#include "mx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



namespace mx
{


	static int alpha_LineSize(int width)
	{

		int back = width;
		int counter;
		for(counter = 0; back != 0; counter++)
			back >>= 1;
		back = 1 << counter;
		if(back == 2*width) back >>= 1;
		return back;
	}

	u32 map_rgb(u8 r, u8 g, u8 b)
	{
		return ((u32)(((u8)(r)|((u32)((u8)(g))<<8))|(((u32)(u8)(b))<<16)));
	}



	mxSurface::mxSurface()
	{
		width = height = tw = th = 0;
		data = 0;

	}

	mxSurface::~mxSurface()
	{

		if(data != 0)
		{

			free(data);
			data = 0;

		}

	}


	int mxSurface::createSurface(int w, int h)
	{

		width = w;
		height = h;
		tw = alpha_LineSize(width);
		th = alpha_LineSize(height);
		data = (void*) malloc ( sizeof(u32) * (tw * th) );
		return 1;
	}

	void mxSurface::setPixel(int x, int y, unsigned int color)
	{
		static u32 *ptr;
		ptr = (u32*) data;
		ptr[x+(y*tw)] = color;

	}

	unsigned int mxSurface::getPixel(int x, int y)
	{
		static u32 *ptr;
		ptr = (u32*) data;
		return ptr[x+(y*tw)];

	}

	bool mxSurface::releaseSurface()
	{



		if(data)
		{


			free(data);
			data = 0;


		}




		return true;
	}

	const void *mxSurface::getData() const {
		return data;
	}



	bool mxSurface::loadImage(const char *source)
	{

		FILE *fptr = 0;
		long offset, size;
		short type, bitcount;
		u32 width, height;
		unsigned int i = 0;
		unsigned int x,q;
		int y=0;
	


		fptr = fopen(source,"rb");
		if(!fptr)
		return 0;
		fread(&type, sizeof(short), 1, fptr);
		if(type != 0x4D42) {
			fclose(fptr);
			return false;
		}

		fseek(fptr, 10, SEEK_SET);
		fread(&offset, sizeof(long), 1, fptr);
		fseek(fptr, 4, SEEK_CUR);
		fread(&width, sizeof(long), 1, fptr);
		fread(&height, sizeof(long), 1, fptr);
		fseek(fptr, 2, SEEK_CUR);
		fread(&bitcount, sizeof(short), 1, fptr);
		if(bitcount != 24) {
			fclose(fptr);
			return false;
		}
		fseek(fptr, 4, SEEK_CUR);
		fread(&size, sizeof(long), 1, fptr);
		fseek(fptr,16,SEEK_CUR);
		
		//surface = (Surface*) malloc ( sizeof(Surface) );
		//surface->w = width;
		//surface->h = height;
		this->width = width;
		this->height = height;
		tw = alpha_LineSize(width);
		th = alpha_LineSize(height);
		data = malloc ( sizeof(u32) * (tw * th) );
	
		if(!data)
		{
			fclose(fptr);
			return false;
		}
	


		for(y = height-1; y > -1; y--)
		{	
			for(x = 0; x < width; x++)
			{
				q = x + y * width;
				u8 b,g,r,w;
				b = fgetc(fptr);
				g = fgetc(fptr);
				r = fgetc(fptr);
				w = 255;
				{
					u32 *s;
					s = (u32*) data;
					s[x+(y*tw)] = map_rgb(r,g,b);
	
				}
	

			}
			for(i = 0; i <  width % 4; i++)
				fgetc(fptr);
		}


		fclose(fptr);

		return true;
	}

	


	bool mxSurface::createImageRaw(void *buffer)
	{

		
		long offset, size;
		short type, bitcount;
		u32 width, height;
		unsigned int i = 0;
		unsigned int x,q;
		int y=0;
	
		mxDataStream stream(buffer);

		stream.fRead(&type, sizeof(short));
		if(type != 0x4D42) {
			return false;
		}

		stream.fSeekSet(10);
		stream.fRead(&offset, sizeof(long));
		stream.fSeekFwd(4);
		stream.fRead(&width, sizeof(long));
		stream.fRead(&height, sizeof(long));
		stream.fSeekFwd(2);
		stream.fRead(&bitcount, sizeof(short));
		if(bitcount != 24) {
			return false;
		}
		stream.fSeekFwd(4);
		stream.fRead(&size, sizeof(long));
		stream.fSeekFwd(6);
		
		this->height = height;
		tw = alpha_LineSize(width);
		th = alpha_LineSize(height);
		data = malloc ( sizeof(u32) * (tw * th) );
	
		if(!data)
		{
			return false;
		}
	


		for(y = height-1; y > -1; y--)
		{	
			for(x = 0; x < width; x++)
			{
				q = x + y * width;
				u8 b,g,r,w;
				b = stream.fgetc();
				g = stream.fgetc();
				r = stream.fgetc();
				w = 255;
				{
					u32 *s;
					s = (u32*) data;
					s[x+(y*tw)] = map_rgb(r,g,b);
	
				}
	

			}
			for(i = 0; i <  width % 4; i++)
				stream.fgetc();
		}


		


		




		return true;

	}




	mxDataStream::mxDataStream(void *buffer)
	{
		data = buffer;
		fpos = 0;
	}

	void mxDataStream::fRead(void *variable, unsigned int num_bytes)
	{

		char *pdata = (char*) data + fpos;
		memcpy(variable, (void*)pdata, num_bytes);
		fpos += num_bytes;
	}

	void mxDataStream::fSeekFwd(unsigned int pos)
	{
		fpos += pos;
	}

	void mxDataStream::fSeekSet(unsigned int pos)
	{
		fpos = pos;
	}

	char mxDataStream::fgetc()
	{
		char *pdata = (char*) data + (++fpos);
		
		return *pdata;
	}


	void InitFont(mxFont *m, int width, int height, int color) {
		int l,p,i,z;
		m->mx = width;
		m->my = height;
		for(l = 0; l <= 127; l++) {
			m->letters[l].fnt_ptr = (int**) malloc ( sizeof(int*) * width);
			for(p = 0; p < width; p++) {
				m->letters[l].fnt_ptr[p] = (int*) malloc ( sizeof(int) * height);
			}
			for(i = 0; i < width; i++) {
				for(z = 0; z < height; z++) {
					m->letters[l].fnt_ptr[i][z] = color;
				}
			}
		}
		m->tcolor = 0x0;
	}

	mxFontObject::~mxFontObject()
	{

		if(font != 0)
		{

			freeFont(font);

		}

	}

	mxFontObject::mxFontObject() {}

	mxFontObject::mxFontObject(char *file_name)
	{

		createFont(file_name);
	}
	

	mxFontObject::mxFontObject(void *buffer)
	{
		createFromData(buffer);

	}

	int mxFontObject::createFont(char *file_name)
	{
		
		FILE *fptr = fopen(file_name, "rb");
		int q = 0,mx = 0,my = 0;
		mxFont *fnt;
		int i,z,p;
		if(!fptr) return 0;
	

		fnt = (mxFont*)malloc(sizeof(mxFont));
		fread((char*)&q, sizeof(int), 1, fptr);

		if(q == -100) {
		fread((char*)&mx, sizeof(int), 1, fptr);
		fread((char*)&my, sizeof(int), 1, fptr);
		fread((char*)&fnt->tcolor, sizeof(int), 1, fptr);


		if(mx < 0 || mx < 0 || mx > 250 || my > 250) {
			// invalid font file
			fprintf(stderr, "Error invalid font file format!\n");
			free(fnt);
			return 0;
		}
			InitFont(fnt, mx, my, fnt->tcolor);

			for(p = 0; p <= 127; p++)
			for(i = 0; i < fnt->mx; i++) {
				for(z = 0; z < fnt->my; z++) {
		
					fread((char*)&fnt->letters[p].fnt_ptr[i][z], sizeof(int), 1, fptr);

	
				}
			}
		}
		fclose(fptr);
		font = fnt;
		return 1;

	}



	int mxFontObject::createFromData(void *buffer)
	{

		mxDataStream stream(buffer);

		int q = 0,mx = 0,my = 0;
		mxFont *fnt;
		int i,z,p;
	
		fnt = (mxFont*)malloc(sizeof(mxFont));
		stream.fRead((char*)&q, sizeof(int));

		if(q == -100) {
		
		stream.fRead((char*)&mx, sizeof(int));
		stream.fRead((char*)&my, sizeof(int));
		stream.fRead((char*)&fnt->tcolor, sizeof(int));


		if(mx < 0 || mx < 0 || mx > 250 || my > 250) {
			// invalid font file
			fprintf(stderr, "Error invalid font file format!\n");
			free(fnt);
			return 0;
		}
			InitFont(fnt, mx, my, fnt->tcolor);

			for(p = 0; p <= 127; p++)
			for(i = 0; i < fnt->mx; i++) {
				for(z = 0; z < fnt->my; z++) {
		
					stream.fRead((char*)&fnt->letters[p].fnt_ptr[i][z], sizeof(int));

	
				}
			}
		}
		



		font = fnt;
		return 1;

	}


	void mxFontObject::freeFont(mxFont *f)
	{
		free(f);
	}



}

