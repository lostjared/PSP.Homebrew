all:
	echo "#define FOR_PC" > platform.h
	gcc mpgame.c -c `sdl-config --cflags`
	gcc start.c -c `sdl-config --cflags`
	gcc mpx2.c -c `sdl-config --cflags`
	gcc mxfont.c -c `sdl-config --cflags`
	gcc pixelbuffer.c -c `sdl-config --cflags`
	gcc pixelbuffer.o mxfont.o mpx2.o mpgame.o start.o `sdl-config --libs` -o ./MasterPieceX2/mpx2
	cp ./MasterPieceX2/mpx2 ./TuxBlocks/tuxblocks
	echo "" > platform.h
static: all
	gcc -static pixelbuffer.o mxfont.o mpx2.o mpgame.o start.o `sdl-config --libs` -luser32 -lwinmm -lgdi32 -o ./MasterPieceX2/mpx2
	cp ./MasterPieceX2/mpx2 ./TuxBlocks/tuxblocks
clean:
	rm -f *.o