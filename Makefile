CC := gcc
LIBS :=
CFLAGS := -I src/

.PHONY: all
all: build/main

.PHONY: objects
objects: $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $(CFLAGS) $< -o $@

build/main: $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
	mkdir -p build
	${CC} build/*.o ${LIBS} -o $@

.PHONY: debug
debug: CFLAGS+=-g -Wall -Werror -Wpedantic
debug: LIBS+=
debug: all

.PHONY: clean
clean:
	rm -rf build/
