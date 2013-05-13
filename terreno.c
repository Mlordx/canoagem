#include <stdlib.h>
#include "terreno.h"
#include "utils.h"

struct terreno{
    char tipo;
    float velocidade;
};


Terreno novoTerreno(char tipo, float velocidade)
{
    Terreno terrTemp = mallocSafe(sizeof(Terreno*));

    terrTemp->tipo = tipo;
    terrTemp->velocidade = velocidade;

    return terrTemp;
}

void freeTerreno(Terreno temp)
{
    free(temp);
}


float getVelocidade(Terreno terr)
{
    return terr->velocidade;
}

char getTipo(Terreno terr)
{
    return terr->tipo;
}

void setVelocidade(Terreno terr, float vel)
{
    terr->velocidade = vel;
}

void setTipo(Terreno terr, char tipo)
{
    terr->tipo = tipo;
}
