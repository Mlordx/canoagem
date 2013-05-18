#ifndef LINHAT_H
#define LINHAT_H

#include "terreno.h"


void imprimeLinhaN(linhaT);


typedef struct linhat *linhaT;

linhaT novaLinha(int tam, int margE, int margD);

int geraObstaculo(linhaT, int);

Terreno getTerreno(linhaT, int);

int getMargEsq(linhaT);

int getMargDir(linhaT);

int temBarreira(linhaT);

void imprimeLinha(linhaT);

void freeLinha(linhaT);

float getFluxo(linhaT);

void setFluxo(linhaT, float);

void igualaFluxo(linhaT, linhaT);

#endif
