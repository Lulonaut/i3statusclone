CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -Wno-missing-field-initializers -g
SRC=main.c config.h block.h block.c
FILENAME=i3statusc

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(FILENAME)

clean:
	@-rm $(FILENAME)