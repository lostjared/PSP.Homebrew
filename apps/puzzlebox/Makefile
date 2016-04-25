TARGET = lostpuzzlebox
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += `$(PSPBIN)/sdl-config --libs`


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = LostPuzzleBox
PSP_EBOOT_ICON = brownies.png
# PSP_EBOOT_PIC1 = test.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak