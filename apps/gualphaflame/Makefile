TARGET = mxpsp_gualpha
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += 
LIBS += -lstdc++ -lmxpsp -lpsppower -lpspgu -lpspgum

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = GuAlphaFlame 


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

