CFLAGS= -Wall -pedantic -g -Wno-unused-result -lm
CC=gcc
Allegro = -lallegro -lallegro_primitives -lallegro_ttf  -lallegro_image -lallegro_dialog -lallegro_font -lallegro_ttf


#-------------------------------------------------



ep3: main.o terreno.o rio.o utils.o list.o linhaT.o testes.o visual.o barco.o vetor2D.o parser.o scanner.o parser.h
	$(CC) main.o terreno.o rio.o utils.o list.o linhaT.o barco.o vetor2D.o testes.o parser.o scanner.o visual.o -o ep3 -lm $(Allegro) -lfl

main.o: main.c parser.h
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

parser.o: parser.c
	$(CC) -c parser.c

scanner.o: scanner.c
	$(CC) -c scanner.c

scanner.c: flex.l parser.h
	flex -o scanner.c flex.l

parser.c parser.h: parser.y
	bison --defines=parser.h -o parser.c parser.y

clean:
	rm *.o *~
