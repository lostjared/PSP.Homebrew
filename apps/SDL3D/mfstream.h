#ifndef __MXFSTREAM__H_
#define __MXFSTREAM__H_


class mfstream {
public:
	FILE *fptr;

	mfstream() { fptr = 0; }
	void open(const char *buf, int flags) {
		fptr = fopen(buf, "r");
	}
	int is_open() { return ( fptr == 0) ? 0 : 1; }
	int eof() { return feof(fptr); }
	void close() {
		if(fptr)
		fclose(fptr);
	}

};

#endif
