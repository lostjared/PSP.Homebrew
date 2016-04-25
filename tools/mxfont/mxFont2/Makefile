CC=i586-mingw32msvc-g++
WINDRES=i586-mingw32msvc-windres

LDFLAGS= -mwindows -lkernel32 -luser32 -lgdi32 -lwinmm -lcomctl32 -lshlwapi
CFLAGS=

all:
	$(WINDRES) mxfont.rc -o fontres.o
	$(CC) main.cpp -c
	$(CC) main.o fontres.o -o mxfont.exe $(LDFLAGS)	
clean:
	rm -rf *~ *.o *.exe
