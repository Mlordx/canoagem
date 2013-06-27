#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vetor2D.h"
#include "utils.h"

struct vetor2d
{
    float x;
    float y;
};

Vetor2D novoVetor(float x, float y)
{
    Vetor2D vetor;
    vetor = mallocSafe(sizeof(*vetor));
    vetor->x = x;
    vetor->y = y;
    return vetor;
}


float getVetorX(Vetor2D vetor)
{
    if(vetor) return vetor->x;
    fprintf(stderr, "Erro em vetor2D: Vetor nulo.\n");
    return 0;
}

float getVetorY(Vetor2D vetor)
{
    if(vetor) return vetor->y;
    fprintf(stderr, "Erro em vetor2D: Vetor nulo.\n");
    return 0;

}


void setVetorX(Vetor2D vetor, float x)
{
    if(vetor) vetor->x = x;
    else fprintf(stderr, "Erro em vetor2D: Vetor nulo.\n");

}
void setVetorY(Vetor2D vetor, float y)
{
    if(vetor) vetor->y = y;
    else fprintf(stderr, "Erro em vetor2D: Vetor nulo.\n");
}

float getModulo(Vetor2D vetor)
{
    float x, y;
    x = getVetorX(vetor);
    y = getVetorY(vetor);
    return sqrt((x*x)+(y*y));
}

void rotVetor(Vetor2D vetor, float ang)
{
    float mod;

    ang += getAngulo(vetor);

    mod = getModulo(vetor);
    setVetorX(vetor,mod*cos(ang));
    setVetorY(vetor,mod*sin(ang));

}

float getAngulo(Vetor2D vetor)
{
    return atan(getVetorY(vetor)/getVetorX(vetor));
}


