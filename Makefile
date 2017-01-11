CC=gcc
CFLAGS=-Wall -Isource
DEPS=source/hello.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

build/index: source/index.o source/hello.o
	$(CC) $(CFLAGS) -o $@ $^

.phony: clean
clean:
	rm -f build/index source/*.o
