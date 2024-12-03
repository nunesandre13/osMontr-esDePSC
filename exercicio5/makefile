


LIBRARY = -lcurl -ljansson
CFLAGS = -g -std=c2x


ex5: mainEx5.o helpers.o commands.o
	gcc mainEx5.o helpers.o commands.o -L../exercicio4/lib -lex4 -o ex5 $(LIBRARY) $(CFLAGS)


mainEx5.o: mainEx5.c
	gcc -c mainEx5.c -I../exercicio3 -I./lib $(CFLAGS) 


helpers.o: helpers.c
	gcc -c helpers.c -I../exercicio3 -I./lib $(CFLAGS) 


commands.o: commands.c
	gcc -c commands.c -I../exercicio3 -I./lib $(CFLAGS) 


clean:
	rm -f *.o ex5
