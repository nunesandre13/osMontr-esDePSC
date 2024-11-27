



LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

ex5: mainEx5.o help3.o list.o cart.o products.o users.o
	gcc mainEx5.o help3.o list.o cart.o products.o users.o -o ex5 -Wall $(LIBRARY) $(CFLAGS)

mainEx5.o: mainEx5.c
	gcc mainEx5.c -c $(CFLAGS)

cart.o: ../exercicio3/cart.c
	gcc ../exercicio3/cart.c -c $(CFLAGS)

products.o: ../exercicio3/products.c
	gcc ../exercicio3/products.c -c $(CFLAGS)

users.o: ../exercicio3/users.c
	gcc ../exercicio3/users.c -c $(CFLAGS)

help3.o: ../exercicio3/help3.c
	gcc ../exercicio3/help3.c -c $(CFLAGS)

list.o: ../exercicio3/list.c
	gcc ../exercicio3/list.c -c $(CFLAGS)

clean:
	rm *.o ex5




