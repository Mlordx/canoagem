#ifndef LINHAT_H
#define LINHAT_H

#include "terreno.h"





typedef struct linhat *linhaT;

void imprimeLinhaN(linhaT);

linhaT geraLinha(linhaT linhaAnt, int tamMin);

linhaT novaLinha(int tam, int margE, int margD);

int geraObstaculo(linhaT, int);

Terreno getTerreno(linhaT, int);

int getMargEsq(linhaT);

int getMargDir(linhaT);

int getLinhaTam(linhaT);

int tamBarreira(linhaT);

void imprimeLinha(linhaT);

void freeLinha(linhaT);

float getFluxo(linhaT);

void setFluxo(linhaT, float);

void igualaFluxo(linhaT, linhaT);

int inicioObst(linhaT);

#endif
