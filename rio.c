#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include "terreno.h"
#include "fila.h"




linhaT geraLinha(linhaT linhaAnt, Rio nilo);

/*static Terreno** alocaFase(int lin, int col);*/

struct rio
{
    Fila linhas;
    float fluxo;
    int tamMin;
    int lin;
    int col;
};




void atualizaRio(Rio nilo)
{
    int i, numAleatorio, ultimaBarr = 0;
    Fila fila = nilo->linhas;
    linhaT temp, novaLinha;

    temp = removeFila(fila);
    novaLinha = geraLinha(temp, nilo);
    insereFila(fila,novaLinha);

    for(i=0;i<nilo->lin-1; i++)
    {
      if(temBarreira(temp) && i<=nilo->lin/4) ultimaBarr = 1; /*Verifica a distancia da ultima barreira*/
      insereFila(fila, temp);
      temp = removeFila(fila);
    }

    freeLinha(temp);

    if(!ultimaBarr && rand()*1.0/RAND_MAX <= PROB_OBST)
    {
      novaLinha = removeFila(fila);
      temp = removeFila(fila);

      numAleatorio = rand()%((getMargDir(novaLinha)-getMargEsq(novaLinha))/2-TAM_MIN_BARREIRA)+TAM_MIN_BARREIRA;
      geraObstaculo(novaLinha,numAleatorio);
      igualaFluxo(temp, novaLinha);
      insereFila(fila, novaLinha);
      insereFila(fila, temp);

      for(i=0;i<nilo->lin-2;i++) insereFila(fila,removeFila(fila));
    }

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
    insereFila(nilo->linhas,linhaTemp);

    for(i=1; i < nilo->lin; i++)
    {
         linhaTemp = geraLinha(linhaTemp, nilo);
         insereFila(nilo->linhas, linhaTemp);
    }


}

void desenhaRio(Rio nilo)
{
    int i;
    linhaT temp;

  for(i=0; i<nilo->lin; i++)
  {
    temp = removeFila(nilo->linhas);
    imprimeLinha(temp);
    insereFila(nilo->linhas,temp);
  }

}



Rio alocaRio(int lin, int col, float fluxo, int tamMin)
{
    Rio nilo = mallocSafe(sizeof (struct rio));

    nilo->linhas = filaInit();
    nilo->col = col;
    nilo->lin = lin;


    if(fluxo > 0) nilo->fluxo = fluxo;
    else nilo->fluxo = FLUXO_DEFAULT;

    if(tamMin > 0) nilo->tamMin = tamMin;
    else nilo->tamMin = TAM_MIN_DEFAULT;

    return nilo;

}


