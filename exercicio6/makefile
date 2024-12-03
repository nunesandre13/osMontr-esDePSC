


LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x

all: ./lib/libcategory.so

ex6: mainEx6.o commands.o helpers.o 
	gcc mainEx6.o helpers.o commands.o -L../exercicio4/lib -lex4 -o ex6 $(LIBRARY) $(CFLAGS)

mainEx6.o: mainEx6.c
	gcc -c mainEx6.c -I../exercicio3 -I./lib $(CFLAGS) 

commands.o: ../exercicio5/commands.c
	gcc -c ../exercicio5/commands.c -I../exercicio3 -I./lib $(CFLAGS) 

helpers.o: ../exercicio5/helpers.c
	gcc -c ../exercicio5/helpers.c -I../exercicio3 -I./lib $(CFLAGS) 

./lib/libcategory.so: category.o
	gcc -shared category.o -o ./lib/libcategory.so

category.o: category.c
	gcc -c -fpic category.c

clean:
	rm -f *.o ex6 

clean_lib:
	rm ./lib/libcategory.so
