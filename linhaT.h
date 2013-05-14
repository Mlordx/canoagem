#include "terreno.h"

typedef struct linhat *linhaT;

linhaT novaLinha(int tam, int margE, int margD);

void geraObstaculo(linhaT, int);

Terreno getTerreno(linhaT, int);

int getMargEsq(linhaT);

int getMargDir(linhaT);

void imprimeLinha(linhaT);

void freeLinha(linhaT);
