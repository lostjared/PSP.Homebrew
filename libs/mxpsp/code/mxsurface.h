#ifndef _MX_SURFACE_H_PSP_
#define _MX_SURFACE_H_PSP_



namespace mx
{



	class mxDisplay;


	class mxSurface {

	public:
		mxSurface();
		~mxSurface();
		bool loadImage(const char *filename);
		bool createImageRaw(void *buffer);
		int  createSurface(int w, int h);
		bool releaseSurface();
		unsigned int getPixel(int x, int y);
		void setPixel(int x, int y, unsigned int color);
		const void *getData() const;
		int width, height, tw, th;
	protected:

		void *data;

		friend class mxDisplay;

	};



	class mxDataStream {

	public:
		explicit mxDataStream(void *buffer);
		void fRead(void *variable, unsigned int size_bytes);
		void fSeekFwd(unsigned int pos);
		void fSeekSet(unsigned int pos);
		char fgetc();

	protected:
		void *data;
		unsigned int  fpos;


	};


	typedef struct mxFont {
		int mx;
		int my;
		int tcolor;
		struct letter {
			int **fnt_ptr;
		} letters[128];


	} MX_Font;

	class mxFontObject {
	
	public:
		mxFontObject();
		~mxFontObject();
		
		mxFontObject(char *file_name);
		mxFontObject(void *buffer);

		int createFont(char *file_name);
		int createFromData(void *buffer);
		void freeFont(mxFont *f);

		mxFont *font;

	};

}






#endif

