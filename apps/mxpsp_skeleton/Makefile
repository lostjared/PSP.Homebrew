TARGET = mxpsp_skelton
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += 
LIBS += -lstdc++ -lmxpsp -lpsppower -lpspgu -lpspgum

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = mxpsp_skeleton


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak