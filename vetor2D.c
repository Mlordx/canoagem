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

void freeVetor(Vetor2D vetor)
{
  free(vetor);
}

Vetor2D somaVetores(Vetor2D vetor1, Vetor2D vetor2)
{
  float x,y;

  x = vetor1->x + vetor2->x;
  y = vetor2->y + vetor1->y;

  return novoVetor(x,y);
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
    setVetorX(vetor,mod*sin(ang));
    setVetorY(vetor,mod*cos(ang));

}

float getAngulo(Vetor2D vetor)
{
  if(getVetorX(vetor) == 0 && getVetorY(vetor) == 0) return 0;

  return acos( getVetorX(vetor)/getModulo(vetor) );


/*  if(getVetorX(vetor)== 0 && getVetorY(vetor) != 0)
  {
    printf("HUE");
    return getVetorY(vetor)> 0 ? PI/2 : 3*PI/2;
  }
  if(getVetorY(vetor) == 0) return getVetorX(vetor) < 0? PI : 0;
  return atan(getVetorY(vetor)/getVetorX(vetor));*/
}


