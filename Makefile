CC = gcc
CFLAGS = -g -Wall -Wextra

MAIN = bracomec

SOURCES = $(wildcard src/bracomec/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

bin/$(MAIN): src/$(MAIN)_teste.c $(OBJECTS)
	$(CC) $(CFLAGS) -I./src/$(MAIN) -o $@ $< $(OBJECTS)

clean:
	rm -fv bin/$(MAIN) src/*.o src/**/*.o ./**/**/*~ ./**/*~ *~
