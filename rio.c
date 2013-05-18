#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include "terreno.h"
#include "list.h"




linhaT geraLinha(linhaT linhaAnt, Rio nilo);

/*static Terreno** alocaFase(int lin, int col);*/

struct rio
{
    List linhas;
    float fluxo;
    int tamMin;
    int lin;
    int col;
};




int atualizaRio(Rio nilo)
{
    int numAleatorio, ultimaBarr = 0, tamMaxObs, status;
    List lista = nilo->linhas;
    linhaT temp, novaLinha;

    status = SUCESSO_ATUALIZA;

    mvEOL(lista);
    mvNext(lista);
    temp = getItem(lista);
    if(temp == NULL)
    {
      fprintf(stderr,"Erro ao tentar ler as linhas do rio");
      return FALHA_ATUALIZA;
    }
    novaLinha = geraLinha(temp, nilo);
    if(novaLinha == NULL)
    {
      fprintf(stderr,"Erro ao tentar gerar uma nova linha");
      return FALHA_ATUALIZA;
    }



    ultimaBarr = 0;
    while(!isEOL(lista))
    {
      ultimaBarr++;
      temp = getItem(lista);
      if(temp == NULL)
      {
        fprintf(stderr,"Erro ao tentar ler as linhas do rio");
        return FALHA_ATUALIZA;
      }
      mvNext(lista);
      if(temBarreira(temp)) break;
    }


    if(ultimaBarr>(nilo->lin/4) && rand()*1.0/RAND_MAX <= PROB_OBST)
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
          fprintf(stderr,"Erro ao tentar criar obstáculo");
          status = FALHA_OBST;
        }
      }
    }
    setFluxo(novaLinha, nilo->fluxo); /*Necessário devido a erro de precisão do float*/


    mvEOL(lista);
    insertList(lista,novaLinha);
    mvPrev(lista);
    freeLinha(getItem(lista));
    removeList(lista);

    return status;

}

linhaT geraLinha(linhaT linhaAnt, Rio nilo)
{
    int novaMargEsq, novaMargDir, margDir, margEsq;
    linhaT linhaNova;

    margEsq = getMargEsq(linhaAnt);
    margDir = getMargDir(linhaAnt);

    printf("HUEEEE: %d %d\n", margDir, margEsq);

    do{
        novaMargDir = rand()%3 -1 + margDir;
        novaMargEsq = rand()%3 -1 + margEsq;

    } while(novaMargDir - novaMargEsq < nilo->tamMin || novaMargEsq <= 0 || novaMargDir >= nilo->col-1);

    linhaNova = novaLinha(nilo->col,novaMargEsq, novaMargDir);
    igualaFluxo(linhaAnt, linhaNova);


    return linhaNova;



}

void rioInit(Rio nilo)
{
    int i, margEsq, margDir, margMax;
    linhaT linhaTemp;
    srand(666);


    margMax = (nilo->col - nilo->tamMin)/2;
    margEsq = rand()%margMax + 1;
    margDir = nilo->col - (rand()%margMax+1);

    linhaTemp = novaLinha(nilo->col, margEsq,margDir);
    setFluxo(linhaTemp, nilo->fluxo);
    insertList(nilo->linhas,linhaTemp);
    mvNext(nilo->linhas);

    for(i=1; i < nilo->lin; i++)
    {
         linhaTemp = geraLinha(linhaTemp, nilo);
         insertList(nilo->linhas, linhaTemp);
         mvNext(nilo->linhas);
    }


}

void desenhaRio(Rio nilo)
{
  linhaT temp;

  mvEOL(nilo->linhas);
  mvNext(nilo->linhas);

  while(!isEOL(nilo->linhas))
  {
    temp = getItem(nilo->linhas);
    imprimeLinha(temp);
    mvNext(nilo->linhas);
  }


}



Rio alocaRio(int lin, int col, float fluxo, int tamMin)
{
    Rio nilo = mallocSafe(sizeof (struct rio));

    nilo->linhas = listInit();
    nilo->col = col;
    nilo->lin = lin;


    if(fluxo > 0) nilo->fluxo = fluxo;
    else nilo->fluxo = FLUXO_DEFAULT;

    if(tamMin > 0) nilo->tamMin = tamMin;
    else nilo->tamMin = TAM_MIN_DEFAULT;

    return nilo;

}


linhaT getLinha(Rio nilo,int ind)
{
  linhaT linhaTemp;
  int i;

  if(ind > nilo->lin) return NULL;

  mvEOL(nilo->linhas);
  for(i=0;i<ind;i++) mvNext(nilo->linhas);
  linhaTemp = getItem(nilo->linhas);

  return linhaTemp;
}

int getNLinhas(Rio nilo)
{
  return nilo->lin;
}









