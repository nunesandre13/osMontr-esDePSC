
LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

ex1: mainEx1.o http_get.o
	gcc mainEx1.o http_get.o -o ex1 $(LIBRARY)

mainEx1.o: mainEx1.c
	gcc mainEx1.c -c $(CFLAGS)

http_get.o: http_get.c
	gcc http_get.c -c $(CFLAGS)

clean:
	rm *.o ex1
