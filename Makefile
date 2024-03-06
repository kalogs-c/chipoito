CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c99
BIN = ./bin/chipoito

all:
	$(CC) main.c $(CFLAGS) -o $(BIN) `sdl2-config --cflags --libs`

run:
	$(BIN)
