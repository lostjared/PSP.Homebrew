TARGET = mps
OBJS = psp_sane.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += -lmxf -L/usr/local/pspdev/psp/lib -lSDLmain -lSDL -lm -lGL -L/usr/local/pspdev/psp/sdk/lib -lpspdebug -lpspgu -lpspctrl -lpspge -lpspdisplay -lpsphprm -lpspvfpu -lpspsdk -lpsprtc -lpspaudio -lc -lpspuser -lpsputility -lpspkernel
# `$(PSPBIN)/sdl-config --libs`


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = MasterPiece Same Edition
# PSP_EBOOT_ICON = mpsp.png
PSP_EBOOT_PIC1 = bg.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

pc:
	rm -f *.o
	gcc psp_sane.c `sdl-config --cflags` -lmxf `sdl-config --libs` -o psp_same
 
