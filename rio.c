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




void atualizaRio(Rio nilo)
{
    int i, numAleatorio, ultimaBarr = 0, tamMaxObs;
    List lista = nilo->linhas;
    linhaT temp, novaLinha;

    mvEOL(lista);
    mvNext(lista);
    temp = removeList(lista);

    novaLinha = geraLinha(temp, nilo);
    insertList(lista, temp);
    mvNext(lista);

    ultimaBarr = 0;
    while(!isEOL(lista))
    {
      ultimaBarr++;
      temp = removeList(lista);
      insertList(lista,temp);
      mvNext(lista);
      mvNext(lista);
      if(temBarreira(temp)) break;
    }

    if(ultimaBarr>(nilo->lin/4) && rand()*1.0/RAND_MAX <= PROB_OBST)
    {
      tamMaxObs = (getMargDir(novaLinha)-getMargEsq(novaLinha))*PORC_MAX_BARREIRA-TAM_MIN_BARREIRA;

      if(tamMaxObs<=0)/*Precisa arrumar isso*/
      {
        setFluxo(novaLinha,nilo->fluxo);
        return;
      }

      numAleatorio = rand()%(tamMaxObs)+TAM_MIN_BARREIRA;
      geraObstaculo(novaLinha,numAleatorio);
      setFluxo(novaLinha,nilo->fluxo);
    }
    setFluxo(novaLinha, nilo->fluxo); /*Necessário devido a erro de precisão do float*/

    mvEOL(lista);
    insertList(lista,novaLinha);
    mvPrev(lista);
    freeLinha(removeList(lista));

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
  int i;
  linhaT temp;

  mvEOL(nilo->linhas);
  mvNext(nilo->linhas);

  while(!isEOL(nilo->linhas))
  {
    temp = removeList(nilo->linhas);
    imprimeLinha(temp);
    insertList(nilo->linhas,temp);
    mvNext(nilo->linhas);
    mvNext(nilo->linhas);
  }

  /*mvNext(nilo->linhas);

  while(!isEOL(nilo->linhas))
  {
    temp = removeList(nilo->linhas);
    imprimeLinhaN(temp);
    insertList(nilo->linhas,temp);
    mvNext(nilo->linhas);
    mvNext(nilo->linhas);
  }*/


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


