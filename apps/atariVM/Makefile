TARGET = AtariVM
OBJS = parse.o lex.o symtab.o stack.o icode.o main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += -lmxf `$(PSPBIN)/sdl-config --libs` 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Atari VM
# PSP_EBOOT_ICON = mpsp.png
# PSP_EBOOT_PIC1 = test.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

ats:
	gcc ats-eboot.c -o ats-eboot

psp:
	echo "#define FOR_PSP" > platform.h
	echo "" > program.h
	rm -f *.o

eboot:
	./ats-eboot default.ats program.h
	echo "#define FOR_PSP" > platform.h
	make


pc:
	echo "" > program.h
	echo "" > platform.h
	gcc -c parse.c symtab.c lex.c pixelbuffer.c stack.c mxfont.c icode.c main.c `sdl-config --cflags`
	gcc -o atari-vm parse.o symtab.o lex.o pixelbuffer.o stack.o mxfont.o icode.o main.o `sdl-config --libs`

exe:
	./ats-eboot default.ats program.h
	echo "" > platform.h
	gcc -c parse.c symtab.c lex.c pixelbuffer.c stack.c mxfont.c icode.c main.c `sdl-config --cflags`
	gcc -o program parse.o symtab.o lex.o pixelbuffer.o stack.o mxfont.o icode.o main.o `sdl-config --libs`

