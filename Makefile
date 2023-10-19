CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=sonic

all: $(EXEC)

sonic: gamemaster.o board.o extensions.o rule.o player.o utils.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c gamemaster.o board.o player.o
	$(CC) -o $@ -c $< $(CFLAGS)

gamemaster.o: gamemaster.c gamemaster.h board.o rule.o player.o extensions.o utils.o
	$(CC) -o $@ -c $< $(CFLAGS)

rule.o: rule.c rule.h board.o
	$(CC) -o $@ -c $< $(CFLAGS)	

player.o: player.c player.h board.o rule.o
	$(CC) -o $@ -c $< $(CFLAGS)

board.o: board.c board.h
	$(CC) -o $@ -c $< $(CFLAGS)

extensions.o: extensions.c extensions.h board.o rule.o
	$(CC) -o $@ -c $< $(CFLAGS)	

utils.o: utils.c utils.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o sonic
