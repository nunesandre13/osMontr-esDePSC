
LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x -fPIC


OBJECTS = cart.o products.o users.o help3.o list.o

$(OUTPUT_DIR)/$(LIBRARY_NAME): $(OBJECTS)
	gcc -shared -o ./lib/libex4.so $(OBJECTS) $(LIBRARY) $(CFLAGS)


run:
	gcc mainEx4.c -L./lib -lex4 -I../exercicio3 -o ex4 $(LIBRARY) $(CFLAGS)


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
	rm -f *.o ex4

clean_products:
	> libraryProducts.csv

clean_users:
	> libraryUsers.csv

clean_lib:
	rm ./lib/libex4.so