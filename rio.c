#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include "terreno.h"
#include "list.h"




linhaT geraLinha(linhaT linhaAnt, int tamMin);

/*static Terreno** alocaFase(int lin, int col);*/

struct rio
{
    List linhas;
    float fluxo;
    int tamMin;
    int lin;
    int col;
};


/*
Essa função atualiza o rio em 1 frame. Ou seja,
irá gerar uma nova linha, e irá deletar a mais velha.

*/

int atualizaRio(Rio rioTemp)
{
    int numAleatorio, ultimaBarr = 0, tamMaxObs, status;
    List lista = rioTemp->linhas;
    linhaT temp, novaLinha;

    status = SUCESSO_ATUALIZA;

    mvEOL(lista);
    mvNext(lista);
    temp = getItem(lista);
    if(temp == NULL)
    {
      return FALHA_ATUALIZA;
    }
    novaLinha = geraLinha(temp, rioTemp->tamMin);
    if(novaLinha == NULL)
    {
      return FALHA_ATUALIZA;
    }



    ultimaBarr = 0;
    while(!isEOL(lista))
    {
      ultimaBarr++;
      temp = getItem(lista);
      if(temp == NULL)
      {
        return FALHA_ATUALIZA;
      }
      mvNext(lista);
      if(tamBarreira(temp)) break;
    }


    if(ultimaBarr>rioTemp->lin*DIST_MIN_OBST && rand()*1.0/RAND_MAX <= PROB_OBST)
    {
      tamMaxObs = (getMargDir(novaLinha)-getMargEsq(novaLinha))*PORC_MAX_BARREIRA-TAM_MIN_BARREIRA;

      if(tamMaxObs<=0)
      {
        status = FALHA_OBST;
      }
      else
      {
        numAleatorio = rand()%(tamMaxObs)+TAM_MIN_BARREIRA;
        if(!geraObstaculo(novaLinha,numAleatorio))
        {
          status = FALHA_OBST;
        }
      }
    }
    setFluxo(novaLinha, rioTemp->fluxo); /*Necessário devido a erro de precisão do float*/


    mvEOL(lista);
    insertList(lista,novaLinha);
    mvPrev(lista);
    freeLinha(getItem(lista));
    removeList(lista);

    return status;

}

/*
Função privada que constroi o rio pela primeira vez.

*/
static void rioInit(Rio rioTemp)
{
    int i, margEsq, margDir, margMax;
    linhaT linhaTemp;


    margMax = (rioTemp->col - rioTemp->tamMin)/2;
    margEsq = rand()%margMax + 1;
    margDir = rioTemp->col - (rand()%margMax+1);

    linhaTemp = novaLinha(rioTemp->col, margEsq,margDir);
    setFluxo(linhaTemp, rioTemp->fluxo);
    insertList(rioTemp->linhas,linhaTemp);
    mvNext(rioTemp->linhas);

    for(i=1; i < rioTemp->lin; i++)
    {
         linhaTemp = geraLinha(linhaTemp, rioTemp->tamMin);
         insertList(rioTemp->linhas, linhaTemp);
         mvNext(rioTemp->linhas);
    }


}

/*

Função que imprime o rio na stdout

*/

void desenhaRio(Rio rioTemp)
{
  linhaT temp;

  mvEOL(rioTemp->linhas);
  mvNext(rioTemp->linhas);

  while(!isEOL(rioTemp->linhas))
  {
    temp = getItem(rioTemp->linhas);
    imprimeLinha(temp);
    mvNext(rioTemp->linhas);
  }


}

/*

Função que retorna um rio com o número de linhas, colunas,
com o fluxo e com o tamanho minimo passaod como argumento.


*/

Rio alocaRio(int lin, int col, float fluxo, int tamMin)
{
    Rio rioTemp = mallocSafe(sizeof (struct rio));

    rioTemp->linhas = listInit();
    rioTemp->col = col;
    rioTemp->lin = lin;
    rioTemp->fluxo = fluxo;
    rioTemp->tamMin = tamMin;

    rioInit(rioTemp);

    return rioTemp;

}

/*

Retorna a linhaT do rio correspondente ao índice passado,
considerando que as linhas são numeradas de cima para baixo,
de 1 até N.

*/
linhaT getLinha(Rio rioTemp,int ind)
{
  linhaT linhaTemp;
  int i;

  if(ind > rioTemp->lin) return NULL;

  mvEOL(rioTemp->linhas);
  for(i=0;i<ind;i++) mvNext(rioTemp->linhas);
  linhaTemp = getItem(rioTemp->linhas);

  return linhaTemp;
}

int getNLinhas(Rio rioTemp)
{
  return rioTemp->lin;
}









