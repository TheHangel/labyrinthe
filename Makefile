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

SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,bin/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst src/%.c,bin/%.d,$(SRC_FILES))

all: $(APP)

$(APP): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(APP) $(OBJ_FILES) $(LDFLAGS)

bin/%.o: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEP_FILES)

clean:
	rm -rf bin/*.o bin/*.d $(APP)

.PHONY: clean
