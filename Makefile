all: display.o gb.o memory.o z80.o main

display.o:
	gcc -c src/display.c -o objects/display.o

gb.o:
	gcc -c gb.c -o objects/gb.o

memory.o:
	gcc -c src/memory.c -o objects/memory.o

z80.o:
	gcc -c src/z80.c -o objects/z80.o

main:
	gcc objects/display.o objects/memory.o objects/z80.o objects/gb.o -o gb

clean:
	rm -rf objects/*
	rm gb
