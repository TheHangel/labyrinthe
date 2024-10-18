CC=gcc
CPPFLAGS=-Wall -Wextra -Iinclude
LDFLAGS=-lncurses

APP=bin/app
TEST_BIN=bin/test/

APP_OBJS=bin/main.o bin/maze.o

all: $(APP)

$(APP): $(APP_OBJS)
	$(CC) $(CPPFLAGS) -o $(APP) $(APP_OBJS) $(LDFLAGS)

bin/maze.o: src/maze.c include/maze.h
	$(CC) $(CPPFLAGS) -c src/maze.c -o bin/maze.o

bin/main.o: src/main.c src/maze.c include/maze.h
	$(CC) $(CPPFLAGS) -c src/main.c -o bin/main.o

clean:
	rm -rf bin/*.o $(APP) $(TEST_BIN)

.PHONY: clean
