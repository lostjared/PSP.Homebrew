#include<stdio.h>
#include<stdlib.h>


struct SDL_Font {
	int mx;
	int my;
	int tcolor;
	struct letter {
		int **fnt_ptr;
	};
	struct letter letters[128];
};


void InitFont(struct SDL_Font *m, int width, int height, int color) {
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


void dump_font(struct SDL_Font *fnt, const char *out) {
	int i,z,p;
	FILE *fptr;
	char fname[1024];
	sprintf(fname,"%s.h", out);
	fptr = fopen(fname,"w");
	if(!fptr) return;

	fprintf(fptr, "int %s_array[] = {", out);
	for(p = 0; p <= 127; p++) {
		
		for(i = 0; i < fnt->mx; i++)  {
			for(z = 0; z < fnt->my; z++) {
				fprintf(fptr, "0x%x,", fnt->letters[p].fnt_ptr[i][z]);
			}
		}
	}

	fprintf(fptr, " 0 };");
	fprintf(fptr, "\nint %s_font_w = 0x%x;\n", out, fnt->mx);
	fprintf(fptr, "\nint %s_font_h = 0x%x;\n", out, fnt->my);
	fprintf(fptr, "\nint %s_font_t = 0x%x;\n", out, fnt->tcolor);
	

	fclose(fptr);
}

struct SDL_Font *SDL_InitFont(const char *src) {
	FILE *fptr = fopen(src, "rb");
	int q = 0,mx = 0,my = 0;
	struct SDL_Font *fnt;
	int i,z,p;
	if(!fptr) return 0;

	fnt = (struct SDL_Font*)malloc(sizeof(struct SDL_Font));

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
	return fnt;
}



void SDL_FreeFont(struct SDL_Font *m) {
	int l,i;
	for(l = 0; l <= 127; l++) {
		if(m->letters[l].fnt_ptr) 
			for(i = 0; i < m->mx; i++) 
				free(m->letters[l].fnt_ptr[i]);
	}

	free(m);
}


int mxf2c(const char *src, const char *out) {



	struct SDL_Font *font = SDL_InitFont(src);
	if(!font) {
		fprintf(stderr, "Error font couldnt be opened..");
		return 0;
	}

	dump_font(font,out);

	SDL_FreeFont(font);
	return 1;
}


int main(int argc, char **argv) {


	if(argc != 3) {
		fprintf(stdout, "Error invalid arguments:\n mxf2c font.mxf name");
		return -1;
	}

	if(mxf2c(argv[1],argv[2])) 
		printf("\nSuccessfully converted font output file name %s.h \n", argv[2]);
	else
		printf("\nA Error has occoured\n");

	system("PAUSE");
	return 0;
}