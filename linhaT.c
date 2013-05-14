#include "terreno.h"
#include "linhaT.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


struct linhat
{
  Terreno* linha;
  int margE;
  int margD;
  int tam;
  int barreira;
};

linhaT novaLinha(int tam, int margE, int margD)
{
  int i;
  linhaT lin = mallocSafe(sizeof *lin);

  lin->linha = mallocSafe(tam*sizeof(*(lin->linha)));
  for(i=0; i<tam; i++)
    if(i<margE) lin->linha[i] = novoTerreno(TERRA, 0);
    else if(i<margD) lin->linha[i] = novoTerreno(AGUA, 0);
    else lin->linha[i] = novoTerreno(TERRA, 0);
  lin->margE = margE;
  lin->margD = margD;
  lin->tam = tam;
  lin->barreira = 0;

  return lin;

}

void imprimeLinha(linhaT temp)
{
  int i;
  for (i=0; i<temp->tam; i++)
    printf("%c",getTipo(temp->linha[i]));
  printf("\n");
}

Terreno getTerreno(linhaT linha, int ind)
{
  return linha->linha[ind];
}

void freeLinha(linhaT linha)
{
  int i;

  for(i=0; i < linha->tam; i++)
    freeTerreno(linha->linha[i]);
  free(linha->linha);
  free(linha);

}

int getMargEsq(linhaT lin)
{
  return lin->margE;
}

int getMargDir(linhaT lin)
{
  return lin->margD;
}

int temBarreira(linhaT lin)
{
  return lin->barreira;
}

void geraObstaculo(linhaT lin, int tam)
{
  int inicio,i;


  if(tam>=lin->tam) exit(-1);

  inicio = lin->margE+1+(rand()%(lin->margD-lin->margE-1-(tam)));

  for(i=0;i<tam;i++)
  {
    /*freeTerreno(lin->linha[inicio+i]);*/
    lin->linha[inicio+i] = novoTerreno(TERRA,0);
  }
  lin->barreira = 1;
}

