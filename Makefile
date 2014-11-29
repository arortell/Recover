CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o recover main.c
stable:clean
	$(CC) $(CFLAGS) -o recover main.c
clean:
	rm -vfr *~ recover
