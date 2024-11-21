

LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

ex3: mainEx3.o help.o
	gcc mainEx3.o help.o -o ex3 $(LIBRARY)

mainEx3.o: mainEx3.c
	gcc mainEx3.c -c $(CFLAGS)

help.o: help.c
	gcc help.c -c $(CFLAGS)

clean:
	rm *.o ex3
