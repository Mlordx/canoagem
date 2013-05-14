CFLAGS= -Wall -pedantic -g -Wno-unused-result -lm
CC=gcc

#-------------------------------------------------



ep2: main.o terreno.o rio.o utils.o fila.o linhaT.o
	$(CC) main.o terreno.o rio.o utils.o fila.o linhaT.o -o ep2 -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c


terreno.o: terreno.h terreno.c
	$(CC) $(CFLAGS) -c terreno.c

fila.o: fila.h fila.c
	$(CC) $(CFLAGS) -c fila.c

rio.o: rio.h rio.c
	$(CC) $(CFLAGS) -c rio.c

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

linhaT.o: linhaT.h linhaT.c
	$(CC) $(CFLAGS) -c linhaT.c

clean:
	rm *.o *~
