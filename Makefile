CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
LDFLAGS=-lncurses

APP=bin/app
TEST_BIN=bin/test/

APP_OBJS=bin/main.o bin/maze.o bin/player.o

all: $(APP)

$(APP): $(APP_OBJS)
	$(CC) $(CFLAGS) -o $(APP) $(APP_OBJS) $(LDFLAGS)

bin/maze.o: src/maze.c include/maze.h
	$(CC) $(CFLAGS) -c src/maze.c -o bin/maze.o

bin/player.o: src/player.c include/player.h
	$(CC) $(CFLAGS) -c src/player.c -o bin/player.o

bin/main.o: src/main.c src/maze.c include/maze.h src/player.c include/player.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

clean:
	rm -rf bin/*.o $(APP) $(TEST_BIN)

.PHONY: clean
