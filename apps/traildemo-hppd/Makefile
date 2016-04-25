
TARGET = hppd
OBJS =  doubleup.o 

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += `$(PSPBIN)/sdl-config --libs`


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Trail Demo
PSP_EBOOT_ICON = hppd.png
# PSP_EBOOT_PIC1 = test.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
	


pc:
	g++ doubleup.cpp -c `sdl-config --cflags` 
	g++ doubleup.o -o hppd `sdl-config --libs`