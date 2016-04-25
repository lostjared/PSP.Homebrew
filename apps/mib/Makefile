all:
	g++ -c main.cpp `sdl-config --cflags --cflags`
	g++ main.o -lmxf `sdl-config --libs` -o mib
clean:
	rm -f *.o

