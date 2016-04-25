TARGET = knightstour
OBJS = knightstour.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += -lmxf `$(PSPBIN)/sdl-config --libs`


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Knights Tour
# PSP_EBOOT_ICON = mpsp.png
# PSP_EBOOT_PIC1 = test.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak