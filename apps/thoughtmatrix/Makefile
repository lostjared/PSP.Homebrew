TARGET = WannaBeMatrix
OBJS = dirbrowse.o matrix.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += -lmxf `$(PSPBIN)/sdl-config --libs`  -lpsppower

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = ThoughtMatrix
# PSP_EBOOT_ICON = mpsp.png
# PSP_EBOOT_PIC1 = test.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

pc:
	rm -f *.o
	gcc mxfont.c -c `sdl-config --cflags`
	gcc pixelbuffer.c -c `sdl-config --cflags`
	gcc matrix.c -c `sdl-config --cflags`
	gcc mxfont.o pixelbuffer.o matrix.o -o matrix `sdl-config --libs`
