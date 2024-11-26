

LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

ex3: mainEx5.o help.o list.o 
	gcc mainEx5.o help.o list.o -o ex3 -Wall $(LIBRARY) $(CFLAGS)

mainEx5.o: mainEx5.c
	gcc mainEx5.c -c $(CFLAGS)

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



