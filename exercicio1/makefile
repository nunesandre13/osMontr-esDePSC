http_get_json: ex1
	./ex1 https://dummyjson.com/products/1

ex1: mainEx1.o http_get.o
	gcc mainEx1.o http_get.o -o ex1 -lcurl -ljansson

mainEx1.o: mainEx1.c
	gcc mainEx1.c -lcurl -ljansson -c -g -std=c2x

http_get.o: http_get.c
	gcc http_get.c -lcurl -ljansson -c -g -std=c2x

clean:
	rm *.o ex1
