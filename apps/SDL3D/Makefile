
TARGET = SDL_3d
OBJS =  main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) 
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += `$(PSPBIN)/sdl-config --libs`  -lstdc++


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = 3DWalk

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
	


pc:
	echo "#define _PC_MODE_H_ 0" > compile_mode.h
	g++ main.cpp -c `sdl-config --cflags`
	g++ main.o -o cube `sdl-config --libs`
pcc:
	echo "#define FOR_PSP" > compile_mode.h
	rm -f *.o masterpiece


