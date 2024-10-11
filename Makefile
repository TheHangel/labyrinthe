CC=gcc
CPPFLAGS=-Wall -Wextra -Iinclude

APP=bin/app
TEST_BIN=bin/test/

APP_OBJS=bin/main.o bin/maze.o
#TEST_OBJS=bin/

$(APP): $(APP_OBJS)
	$(CC) $(CPPFLAGS) -o $(APP) $(APP_OBJS) -lm

bin/maze.o: src/maze.c
	$(CC) $(CPPFLAGS) -c src/maze.c -o bin/maze.o

bin/main.o: src/main.c src/maze.c
	$(CC) $(CPPFLAGS) -c src/main.c -o bin/main.o bin/maze.o

clean:
	rm -f bin/*.o bin/test/*.o $(APP) $(TEST_BIN)

.PHONY: clean
