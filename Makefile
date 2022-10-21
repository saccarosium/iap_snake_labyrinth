CC = gcc
CFLAGS = --std=c99
CINCLUDE = -lncurses
OUTNAME = build/maze

all: mkout
	$(CC) $(CFLAGS) $(CINCLUDE) -o $(OUTNAME) src/*.c

mkout:
	mkdir -p build
