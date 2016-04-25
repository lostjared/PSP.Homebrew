LIB_PATH=/opt/local

all:
	g++ `$(LIB_PATH)/bin/sdl-config --cflags` mxfont_fix.cc -c
	g++ mxfont_fix.o -o mxfont_fix `$(LIB_PATH)/bin/sdl-config --static-libs` $(LIB_PATH)/lib/libSDL_ttf.a $(LIB_PATH)/lib/libfreetype.a $(LIB_PATH)/lib/libz.a  $(LIB_PATH)/lib/libbz2.a 
