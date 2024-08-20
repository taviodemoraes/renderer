CC=gcc
FILES=./src/*.c
EXE=renderer

all: build run clean

build:
	eval $(CC) $(FILES) -o $(EXE) $(shell pkg-config --cflags --libs sdl2) -lm 

run:
	./$(EXE)

clean:
	rm -rf $(EXE)
