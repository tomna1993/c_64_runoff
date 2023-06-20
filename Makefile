CC := gcc
#CFLAGS := 
DEST := ./build/

all: runoff.c
	mkdir -p build
	$(CC) runoff.c -lcs50 -o $(DEST)/runoff 