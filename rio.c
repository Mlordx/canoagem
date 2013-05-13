#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include "terreno.h"




void geraLinha(Terreno* linhaAnt, Terreno* linhaNova, Rio nilo);

static Terreno** alocaFase(int lin, int col);

struct rio
{
    Terreno** fase;
    float fluxo;
    int tamMin;
    int lin;
    int col;
};

static void freeLinha(Terreno* linha, int col)
{
    int i;

    for(i=0; i<col; i++)
        freeTerreno(linha[i]);
    free(linha);
}



void atualizaRio(Rio nilo)
{
    int i;



    nilo->fase[0] =nilo->fase[nilo->lin-1];
    for(i=nilo->lin-1; i>0; i--)
        nilo->fase[i] = nilo->fase[i-1];


    geraLinha(nilo->fase[1],nilo->fase[0], nilo);
}

void geraLinha(Terreno* linhaAnt, Terreno* linhaNova, Rio nilo)
{
    int i, novaMargEsq, novaMargDir, margDir, margEsq;

    for(i=0; getTipo(linhaAnt[i])==TERRA; i++);
    margEsq = i;

    for(i=nilo->col-1; getTipo(linhaAnt[i])==TERRA; i--);
    margDir = i;

    printf("HUEEEE: %d %d\n", margDir, margEsq);

    do{
         novaMargDir = (((1.0*rand())/RAND_MAX) < 0.5)? (margDir - VAR_MARG) : (margDir + VAR_MARG);
         novaMargEsq = (((1.0*rand())/RAND_MAX) < 0.5)? (margEsq - VAR_MARG) : (margEsq + VAR_MARG);

    } while(novaMargDir - novaMargEsq < nilo->tamMin || novaMargEsq <= 0 || novaMargDir >= nilo->col-1);

    for(i=0; i<nilo->col; i++)
        if(i < novaMargEsq) linhaNova[i] = novoTerreno(TERRA,0);
        else if( i < novaMargDir) linhaNova[i] = novoTerreno(AGUA,0);
        else linhaNova[i] = novoTerreno(TERRA,0);







}

void rioInit(Rio nilo)
{
    int i, margEsq, margDir, margMax;
    Terreno* linha1 = nilo->fase[0];


    margMax = (nilo->col - nilo->tamMin)/2;
    margEsq = rand()%margMax + 1;
    margDir = nilo->col - (rand()%margMax+1);

    for(i=0; i < nilo->col; i++)
        if(i<margEsq) linha1[i] = novoTerreno(TERRA, 0);
        else if(i < margDir) linha1[i] = novoTerreno(AGUA, 0);
        else linha1[i] = novoTerreno(TERRA, 0);

    for(i=1; i < nilo->lin; i++)
         geraLinha(nilo->fase[i-1],nilo->fase[i], nilo);






}

void desenhaRio(Rio nilo)
{
    int i,j;

    for(i=0;i<nilo->lin;i++)
    {
        for(j=0;j<nilo->col;j++)
            printf("%c",getTipo(nilo->fase[i][j]));
        printf("\n");
    }

}



Rio alocaRio(int lin, int col, float fluxo, int tamMin)
{
    Rio nilo = mallocSafe(sizeof (struct rio));

    nilo->fase = alocaFase(lin,col);
    nilo->col = col;
    nilo->lin = lin;

    if(fluxo > 0) nilo->fluxo = fluxo;
    else nilo->fluxo = FLUXO_DEFAULT;

    if(tamMin > 0) nilo->tamMin = tamMin;
    else nilo->tamMin = TAM_MIN_DEFAULT;

    return nilo;

}

static Terreno** alocaFase(int lin, int col)
{
    int i, j;
    Terreno** fase = mallocSafe(lin*sizeof(Terreno*));

    for(i = 0; i < lin; i++)
    {
        fase[i] = mallocSafe(col*sizeof(Terreno));
        for(j=0;j<col;j++) fase[i][j] = NULL;
    }

    return fase;
}
