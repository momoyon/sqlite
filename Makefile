CC=gcc
CFLAGS=-Wall -Wextra
LIBS=-lsqlite3

main: main.c
	$(CC) $(CFLAGS) -I./ -o $@ $< -L./ $(LIBS)

clean:
	rm main 2> /dev/null
