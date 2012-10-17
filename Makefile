all:
	gcc -c src/display.c -o objects/display.o
	gcc -c src/memory.c -o objects/memory.o
	gcc -c src/z80.c -o objects/z80.o
	gcc -c gb.c -o objects/gb.o
	gcc objects/display.o objects/memory.o objects/z80.o objects/gb.o -o gb

rm:
	rm -rf objects/*
	rm gb
