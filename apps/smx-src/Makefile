all:
	echo "" > platform.h
	gcc level.c -c `sdl-config --cflags`
	gcc game.c -c `sdl-config --cflags`
	gcc interface.c -c `sdl-config --cflags`
	gcc level.o game.o interface.o -o smx -static -lmxf `sdl-config --libs` -luser32 -lgdi32 -lwinmm
exe: all
	./smx
clean:
	rm -f *.o smx.exe
