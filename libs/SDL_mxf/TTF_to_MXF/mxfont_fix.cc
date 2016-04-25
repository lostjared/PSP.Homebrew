#include "SDL.h"
#include "SDL_ttf.h"
#include<iostream>
#include<string>


struct SDL_Font {
    int mx;
    int my;
    int tcolor;
    struct letter {
        int **fnt_ptr;
    } letters[128];
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

void WriteFont(SDL_Font *m, std::string file_name) {
    
    FILE *fptr = fopen(file_name.c_str(), "wb");
    if(!fptr) {
        
        exit(0);
    }
    int num = -100;
    fwrite((char*)&num, sizeof(int), 1, fptr);
    fwrite((char*)&m->mx, sizeof(int), 1, fptr);
    fwrite((char*)&m->my, sizeof(int), 1, fptr);
    for(int p = 0; p <= 127; ++p) {
        for(int i = 0; i < m->mx; ++i) {
            for(int z = 0; z < m->my; ++z) {
                fwrite((char*)&m->letters[p].fnt_ptr[i][z], sizeof(int), 1, fptr);
            }
        }
    }
    fclose(fptr);
    std::cout << "Wrote file: " << file_name << "\n";
}

int main(int argc, char **argv) {
    
    if(argc != 4) { std::cout << "Error no param. \n" << argv[0] << " font.ttf width height\n" << "\n"; exit(0); }
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(argv[1], width);
    if(!font) {
        std::cout << "Could not open font..\n";
        exit(0);
    }

    SDL_Font *refont = 0;
    refont = (struct SDL_Font*)malloc(sizeof(struct SDL_Font));
    InitFont(refont, width, height, 0x0);
    for(int i = 0; i < 128; ++i) {
        std::string text;
        text += static_cast<char>(i);
        if(text.length() == 0) continue;
        SDL_Color white_color = { 255,255,255 };
        SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), white_color);
        if(text_surface == 0) continue;
        SDL_LockSurface(text_surface);
        unsigned char *buffer = (unsigned char *)text_surface->pixels;
        for(unsigned int x = 0; x < width; ++x) {
            for(unsigned int y = 0; y < height; ++y) {
                if(x < text_surface->w && y < text_surface->h) {
                    unsigned char pix_color = buffer[y*text_surface->pitch+x];
                    refont->letters[i].fnt_ptr[x][y] = 255*pix_color;
                }
            }
        }
        SDL_UnlockSurface(text_surface);
        SDL_FreeSurface(text_surface);
    }
    std::string text_fname = argv[1];
    text_fname += ".mxf";
    WriteFont(refont, text_fname);    
    TTF_CloseFont(font);
    free(refont);
    TTF_Quit();
    SDL_Quit();
    return 0;
}


