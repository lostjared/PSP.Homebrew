#include "mx.h"

extern mxHwnd mxhwnd;
extern mxPaint paint;
extern mxFont font;
extern int linenum;

extern char* getPath(char*);
extern void gameover();

#include"mx.h"
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<unistd.h>

using namespace std;

#define INTRO 1
#define START 2
#define OPTIONS 3
#define CREDITS 4
#define GAME 5
#define HIGHSCORES 6
