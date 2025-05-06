CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/cli.c src/game.c src/hud.c src/input.c
OBJ = $(SRC:.c=.o)
EXEC = build/cyberterminal

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC) src/*.o