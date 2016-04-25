all:
	g++ `/opt/local/bin/sdl-config --cflags` mxfont_fix.cc -c
	g++ mxfont_fix.o -o mxfont_fix `/opt/local/bin/sdl-config --static-libs` /opt/local/lib/libSDL_ttf.a /opt/local/lib/libfreetype.a /opt/local/lib/libz.a  /opt/local/lib/libbz2.a 
