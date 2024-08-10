CC=gcc
FILES=./src/*.c
EXE=renderer
SDL=`sdl-config --cflags --libs`

all: build run clean

build:
	$(CC) $(FILES) -o $(EXE) $(SDL)

run:
	./$(EXE)

clean:
	rm -rf $(EXE)
