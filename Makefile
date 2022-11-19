CC = gcc
CFLAGS = --std=c99 -Wall
CINCLUDE = -lncurses
OUTNAME = build/maze

all: mkout
	$(CC) $(CFLAGS) $(CINCLUDE) -o $(OUTNAME) src/*.c

mkout:
	mkdir -p build

format:
	clang-format -i ./src/*.c ./include/*.h
