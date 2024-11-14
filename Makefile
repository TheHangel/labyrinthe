CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -finput-charset=UTF-8

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	LDFLAGS = -lncursesw
endif

ifeq ($(UNAME_S), Darwin)
	LDFLAGS = -lncurses
endif

APP = bin/app
TESTS = bin/tests

SEED ?= 0

CONSTANTS = -DSEED=$(SEED)

SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,bin/%.o,$(filter-out src/main.c src/test/tests.c, $(SRC_FILES)))
DEP_FILES = $(patsubst src/%.c,bin/%.d,$(SRC_FILES))

TEST_SRC = src/test/tests.c
TEST_OBJ = bin/tests.o

all: $(APP)

$(APP): $(OBJ_FILES) bin/main.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(APP) $(OBJ_FILES) bin/main.o $(LDFLAGS)

bin/%.o: src/%.c
	@mkdir -p bin
	$(CC) $(CONSTANTS) $(CFLAGS) -MMD -c $< -o $@

tests: $(TEST_OBJ) $(OBJ_FILES)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(TESTS) $(TEST_OBJ) $(OBJ_FILES) $(LDFLAGS)

$(TEST_OBJ): $(TEST_SRC)
	@mkdir -p bin
	$(CC) $(CONSTANTS) $(CFLAGS) -MMD -c $< -o $@

doc:
	@mkdir -p doc
	doxygen Doxyfile

zip:
	zip -r labyrinthe.zip *

-include $(DEP_FILES)

clean:
	rm -rf bin/*.o bin/*.d $(APP) $(TESTS)

distclean: clean
	rm -rf bin doc data

.PHONY: clean tests all doc distclean zip
