http_post_json: ex2
	./ex2 https://dummyjson.com/carts/add carrinho.json

ex2: http_post.o mainEx2.o
	gcc http_post.o mainEx2.o -o ex2 -lcurl -ljansson

http_post.o: http_post.c
	gcc http_post.c -c -g -std=c2x -lcurl -ljansson

mainEx2.o: mainEx2.c
	gcc mainEx2.c -c -g -std=c2x -lcurl -ljansson

clean:
	rm *.o ex2
