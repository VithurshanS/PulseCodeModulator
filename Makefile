all:
	gcc -std=c99 -Wall -Wextra mypcm.c lab2.c -o pcm

clean:
	rm -f *.o pcm
