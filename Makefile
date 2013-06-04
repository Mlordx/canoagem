CFLAGS= -Wall -pedantic -g -Wno-unused-result -lm
CC=gcc
Allegro = -lallegro -lallegro_primitives


#-------------------------------------------------



ep2: main.o terreno.o rio.o utils.o list.o linhaT.o testes.o visual.o
	$(CC) main.o terreno.o rio.o utils.o list.o linhaT.o testes.o -o ep2 -lm $(Allegro)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

terreno.o: terreno.h terreno.c
	$(CC) $(CFLAGS) -c terreno.c

fila.o: list.h list.c
	$(CC) $(CFLAGS) -c list.c

rio.o: rio.h rio.c
	$(CC) $(CFLAGS) -c rio.c

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

linhaT.o: linhaT.h linhaT.c
	$(CC) $(CFLAGS) -c linhaT.c

testes.o: testes.h testes.c
	$(CC) $(CFLAGS) -c testes.c

visual.o: visual.h visual.c
	$(CC) $(CFLAGS) -c visual.c

clean:
	rm *.o *~
