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
    else if(i<margD)
    {
       if(getTipo(lin->linha[i-1])==TERRA) lin->linha[i] = novoTerreno(AGUA, 0);
       else lin->linha[i] = novoTerreno(AGUA, (1.0*rand())/RAND_MAX );
    }
    else
    {
      lin->linha[i] = novoTerreno(TERRA, 0);
      if(getTipo(lin->linha[i-1]) == AGUA) setVelocidade(lin->linha[i-1],0);
    }
  lin->margE = margE;
  lin->margD = margD;
  lin->tam = tam;
  lin->barreira = 0;

  return lin;

}

void imprimeLinhaN(linhaT temp)
{
  int i;
  for (i=0; i<temp->tam; i++)
    printf("%0.2f|", getVelocidade(temp->linha[i]));
  printf("    %f\n", getFluxo(temp));
}

void imprimeLinha(linhaT temp)
{
  int i;
  for (i=0; i<temp->tam; i++)
   printf("%c",getTipo(temp->linha[i]));
  printf("  %f\n", getFluxo(temp));
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

int geraObstaculo(linhaT lin, int tam)
{
  int inicio,i, inicioMax;


  if(tam>=lin->tam)
  {
    fprintf(stderr,"Erro ao criar obstáculo: Tamanho do obstáculo maior que do Rio\n");
    return 0;
  }

  if((inicioMax = lin->margD-lin->margE -1 -tam)<5)
  {
    fprintf(stderr,"Erro ao criar obstáculo: Tamanho do obstáculo faria o fluxo zerar\n");
    return 0;
  }

  inicio = lin->margE+1+(rand()%(inicioMax));
  setVelocidade(lin->linha[inicio-1],0);
  setVelocidade(lin->linha[inicio+tam],0);


  for(i=0;i<tam;i++)
  {
    /*freeTerreno(lin->linha[inicio+i]);*/
    lin->linha[inicio+i] = novoTerreno(TERRA,0);
  }
  lin->barreira = 1;

  return 1;
}

float getFluxo(linhaT lin)
{
  int i;
  float soma = 0;

  for(i=0;i < lin->tam; i++)
    soma+= getVelocidade(lin->linha[i]);

  return soma;
}

void setFluxo(linhaT lin, float fluxoNovo)
{
  int i;
  float fluxoAnt;

  fluxoAnt = getFluxo(lin);

  for(i=0;i<lin->tam; i++)
    setVelocidade(lin->linha[i], getVelocidade(lin->linha[i])*(fluxoNovo/fluxoAnt));


}


void igualaFluxo(linhaT lin1, linhaT lin2)
{
  int i;
  float fluxo, velTemp;

  fluxo = getFluxo(lin1);
  setFluxo(lin1,1); /*Para tratarmos com mais facilidade das velocidades*/

  for(i=1; i<(lin1->tam-1); i++)
  {

    if(getTipo(lin2->linha[i-1]) == TERRA || getTipo(lin2->linha[i+1]) == TERRA)
    {
      setVelocidade(lin2->linha[i], 0);
      continue;
    }
    if(getTipo(lin2->linha[i])== AGUA)
    {
      if(getTipo(lin1->linha[i])== TERRA) setVelocidade(lin2->linha[i],0.1);
      else
      {
        velTemp = getVelocidade(lin1->linha[i]) + (1.0*(rand()%3) -1)/10;
        if(velTemp<0) velTemp= 0.1;

        setVelocidade(lin2->linha[i], velTemp);
      }
    }
  }

  setFluxo(lin1,fluxo);
  setFluxo(lin2,fluxo);



}

