#ifndef TERRENO_H
#define TERRENO_H

#define AGUA '.'
#define TERRA '#'

typedef struct terreno *Terreno;

Terreno novoTerreno(char tipo, float velocidade);

void freeTerreno(Terreno);

float getVelocidade(Terreno);

char getTipo(Terreno);

void setVelocidade(Terreno, float);

void setTipo(Terreno, char);

#endif
