CC = gcc
CFLAGS = --std=c99 -Wall -g
CINCLUDE = -lncurses
OUTNAME = build/maze
SH = /usr/bin/env sh

all: compile

challenge: compile
	$(SH) ./scripts/challenge.sh $(word 2, $(MAKECMDGOALS) )

%: 
	echo "...done..."

compile: mkout
	$(CC) $(CFLAGS) $(CINCLUDE) -o $(OUTNAME) src/*.c

mkout:
	mkdir -p build

format:
	clang-format -i ./src/*.c ./include/*.h

