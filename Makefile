CC=gcc
CFLAGS=-Wall -Wextra
LIBS=-l:sqlite3.dll

main: main.c
	$(CC) $(CFLAGS) -I./ -o $@ $< -L./ $(LIBS)

clean:
	rm main.exe 2> /dev/null
