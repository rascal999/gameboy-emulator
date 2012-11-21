all: cartridge.o display.o error.o gb.o memory.o rom.o timer.o z80.o main

cartridge.o:
	gcc -ggdb -Wall -std=c99 -c src/cartridge.c -o objects/cartridge.o

display.o:
	gcc -ggdb -Wall -std=c99 -c src/display.c -o objects/display.o

error.o:
	gcc -ggdb -Wall -std=c99 -c src/error.c -o objects/error.o

gb.o:
	gcc -ggdb -Wall -std=c99 -c gb.c -o objects/gb.o

memory.o:
	gcc -ggdb -Wall -std=c99 -c src/memory.c -o objects/memory.o

rom.o:
	gcc -ggdb -Wall -std=c99 -c src/rom.c -o objects/rom.o

timer.o:
	gcc -ggdb -Wall -std=c99 -c src/timer.c -o objects/timer.o

z80.o:
	gcc -ggdb -Wall -std=c99 -c src/z80.c -o objects/z80.o

main:
	gcc -ggdb -Wall -std=c99 objects/cartridge.o objects/display.o objects/error.o objects/memory.o objects/rom.o objects/timer.o objects/z80.o objects/gb.o -o gb

clean:
	rm -rf objects/*
	rm gb

#gcc -ggdb -Wall -I /usr/include/SDL/ `sdl-config --cflags --libs` -std=c99
#gcc -ggdb -Wall -std=c99
