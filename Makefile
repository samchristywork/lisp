CC := gcc
LIBS := -lm
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

.PHONY: run
run:
	make && ./build/main

.PHONY: watch
watch:
	make clean
	git ls-files | entr -s 'make debug && ./build/main'

.PHONY: list
list:
	@echo Valid Targets:
	@make -qp | awk -F':' '/^[a-zA-Z0-9][^$$#\/\t=]*:([^=]|$$)/ {split($$1,A,/ /);for(i in A)print A[i]}' | sort -u | grep -v "^Makefile$$" | sed 's/^/  - /g'

.PHONY: debug
debug: CFLAGS+=-g -Wall -Werror -Wpedantic
debug: LIBS+=
debug: all

.PHONY: release
release: CFLAGS+=-O2
release: LIBS+=
release: all

.PHONY: clean
clean:
	rm -rf build/
