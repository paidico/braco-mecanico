CC = gcc
CFLAGS = -g -Wall -Wextra

SOURCES = $(wildcard src/bracomec/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

bin/bracomec: src/bracomec_teste.c $(OBJECTS)
	$(CC) $(CFLAGS) -I./src/bracomec -o $@ $< $(OBJECTS)

clean:
	rm -frv bin/* src/*.o src/**/*.o ./**/**/*~ ./**/*~ *~
