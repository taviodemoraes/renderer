CC=gcc
FILES=./src/*.c
EXE=renderer

all: build run clean

build:
	$(CC) $(FILES) -o $(EXE) $(shell pkg-config --cflags --libs sdl2) 

run:
	./$(EXE)

clean:
	rm -rf $(EXE)
