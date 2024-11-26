

LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

ex3: mainEx3.o help.o list.o cart.o products.o users.o
	gcc mainEx3.o help.o list.o cart.o products.o users.o -o ex3 -Wall $(LIBRARY) $(CFLAGS)

mainEx3.o: mainEx3.c
	gcc mainEx3.c -c $(CFLAGS)

cart.o: cart.c
	gcc cart.c -c $(CFLAGS)

products.o: products.c
	gcc products.c -c $(CFLAGS)

users.o: users.c
	gcc users.c -c $(CFLAGS)

help.o: help.c
	gcc help.c -c $(CFLAGS)

list.o: list.c
	gcc list.c -c $(CFLAGS)

clean:
	rm *.o ex3
	
clean_products:
	> products.csv

clean_users:
	> users.csv



