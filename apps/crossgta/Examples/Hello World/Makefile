
PSPSDK=$(shell psp-config --pspsdk-path)
PSPDEV=$(shell psp-config --pspdev-path)/bin
INCLUDE=$(PSPSDK)/include

copy-all: clean all
# This assumes that you have set up a symbolic link called /psp pointing to your memstick drive
	cp tetris.bin /cygdrive/n/psp/savedata/ULES00151S5/
	cp tetris.bin /cygdrive/n/psp/savedata/ULUS10041S5/

all:
	rm -f *.o
	echo "#define FOR_PSP" > platform.h
	$(PSPDEV)/psp-gcc -I $(INCLUDE) -O2 -W -Wall -G0 -fno-pic -mno-abicalls -w -S main.c -o main.s
	$(PSPDEV)/psp-as main.s -o main.o
	$(PSPDEV)/psp-ld --no-warn-mismatch -T psp20bin.x main.o -o main.elf -lc -L/usr/local/
	$(PSPDEV)/psp-strip -s main.elf
	$(PSPDEV)/psp-objcopy -O binary main.elf tetris.bin

pc:
	rm -f *.o
	echo "" > platform.h
	gcc cross_gta_sdl.c -c `sdl-config --cflags`
	gcc main.c -c `sdl-config --cflags`
	gcc cross_gta_sdl.o main.o -o helloworld `sdl-config --libs`

clean:
	rm -rf *~ *.o *.elf *.bin *.s *.bin
 



