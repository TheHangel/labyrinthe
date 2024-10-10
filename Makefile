CC=gcc
CPPFLAGS=-Wall -Wextra

APP=bin/app
TEST_BIN=bin/test/

APP_OBJS=bin/main.o
#TEST_OBJS=bin/

$(APP): $(APP_OBJS)
	$(CC) $(CPPFLAGS) -o $(APP) $(APP_OBJS) -lm

bin/main.o: src/main.c
	$(CC) $(CPPFLAGS) -c src/main.c -o bin/main.o

clean:
	rm -f bin/*.o bin/test/*.o $(APP) $(TEST_BIN)

.PHONY: clean
