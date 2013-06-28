CFLAGS= -Wall -pedantic -g -Wno-unused-result -lm
CC=gcc
Allegro = -lallegro -lallegro_primitives -lallegro_ttf  -lallegro_image


#-------------------------------------------------



ep3: main.o terreno.o rio.o utils.o list.o linhaT.o testes.o visual.o barco.o vetor2D.o
	$(CC) main.o terreno.o rio.o utils.o list.o linhaT.o barco.o vetor2D.o testes.o visual.o -o ep3 -lm $(Allegro)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

barco.o: barco.c
	$(CC) $(CFLAGS) -c barco.c

vetor2D.o: vetor2D.c
	$(CC) $(CFLAGS) -c vetor2D.c


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
