#include <stdlib.h>
#include "terreno.h"
#include "utils.h"

struct terreno{
    char tipo;
    float velocidade;
};


/*
Função que retorna um novo Terreno com o tipo especificado
e com a velocidade especificada.

*/

Terreno novoTerreno(char tipo, float velocidade)
{
    Terreno terrTemp = mallocSafe(sizeof(Terreno*));

    terrTemp->tipo = tipo;
    terrTemp->velocidade = velocidade;

    return terrTemp;
}


/*

Libera a memória alocada pelo terreno passado como argumento.

*/

void freeTerreno(Terreno temp)
{
    free(temp);
}



/*
Retorna a velocidade do terreno passado.

*/

float getVelocidade(Terreno terr)
{
    return terr->velocidade;
}

/*

Retorna o tipo do terreno passado.

*/

char getTipo(Terreno terr)
{
    return terr->tipo;
}


/*

Define a velocidade do terreno passado como argumento.

*/

void setVelocidade(Terreno terr, float vel)
{
    terr->velocidade = vel;
}

/*
Define o tipo do terreno passado como argumento

*/

void setTipo(Terreno terr, char tipo)
{
    terr->tipo = tipo;
}
