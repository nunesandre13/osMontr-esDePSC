
LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

ex2: http_post.o mainEx2.o
	gcc http_post.o mainEx2.o -o ex2 $(LIBRARY)

http_post.o: http_post.c
	gcc http_post.c -c $(CFLAGS)

mainEx2.o: mainEx2.c
	gcc mainEx2.c -c -g -std=c2x $(CFLAGS)
clean:
	rm *.o ex2
