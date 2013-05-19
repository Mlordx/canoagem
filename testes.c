#define SEED_DEFAULT 1234567890
#define NUM_LIN_DEFAULT 30
#define NUM_COL_DEFAULT 100
#define FLUXO_DEFAULT 1
#define TAM_MIN_DEFAULT 5
#define FALHA 0
#define SUCESSO 1

#include "testes.h"
#include "rio.h"
#include "linhaT.h"
#include <stdlib.h>
#include <stdio.h>

int testaMargem(int iteracoes){
  int i;
  Rio nilo;

  printf("Teste da variação maxima das margens\n");
  nilo = alocaRio(NUM_LIN_DEFAULT,NUM_COL_DEFAULT,FLUXO_DEFAULT,0);

    for(i=0;i<iteracoes;i++)
        if(atualizaRio(nilo) == FALHA){
            printf("Falha no teste\n");
            return FALHA;
        }

  printf("O teste não apresentou falhas!\n");
  return SUCESSO;
}

int testaLinhas(int iteracoes){
  int i;
  Rio nilo;

  printf("Teste de linhas\n");
  printf("Numero de linhas = 10000\n");

  nilo = alocaRio(10000,NUM_COL_DEFAULT,FLUXO_DEFAULT,TAM_MIN_DEFAULT);

    for(i=0;i<iteracoes;i++)
        if(atualizaRio(nilo) == FALHA){
            printf("Falha no teste de linhas\n");
            return FALHA;
        }

  printf("Numero de linhas = 5\n");

  nilo = alocaRio(5,NUM_COL_DEFAULT,FLUXO_DEFAULT,TAM_MIN_DEFAULT);

    for(i=0;i<iteracoes;i++)
        if(atualizaRio(nilo) == FALHA){
            printf("Falha no teste de linhas\n");
            return FALHA;

        }

  printf("O teste não apresentou falhas!\n");
  return SUCESSO;
}

int testaFluxo(int iteracoes){
  int i;
  Rio nilo;

  printf("Teste de fluxo\n");
  printf("Fluxo = 0.0001\n");
  nilo = alocaRio(NUM_LIN_DEFAULT,NUM_COL_DEFAULT,0.0001,TAM_MIN_DEFAULT);

    for(i=0;i<iteracoes;i++)
        if(atualizaRio(nilo) == FALHA){
            printf("Falha no teste de fluxo\n");
            return FALHA;
        }

  printf("Teste da constancia do fluxo\n");
  nilo = alocaRio(NUM_LIN_DEFAULT,NUM_COL_DEFAULT,FLUXO_DEFAULT,TAM_MIN_DEFAULT);

  for(i=0;i<iteracoes;i++)
    if(atualizaRio(nilo) == FALHA && /*para ter ao menos 2 linhas*/  (getFluxo(getLinha(nilo,0)) - getFluxo(getLinha(nilo,1))) > 0.0001){
            printf("Falha no teste!\n");
            return FALHA;
       }


  printf("O teste não apresentou falhas!\n");
  return SUCESSO;
}

void testaVariacao(int iteracoes){
  int i;
  Rio nilo;
  int varMinEsq = 0,varMaxEsq = 0, varMinDir = 0, varMaxDir = 0,varMediaEsq = 0,varMediaDir = 0,varEsq = 0, varDir = 0;

  nilo = alocaRio(NUM_LIN_DEFAULT,NUM_COL_DEFAULT,FLUXO_DEFAULT,TAM_MIN_DEFAULT);

    for(i =0; i< iteracoes;i++){
        atualizaRio(nilo);

        varEsq = getMargEsq(getLinha(nilo,0)) - getMargEsq(getLinha(nilo,1));
        varDir = getMargDir(getLinha(nilo,0)) - getMargDir(getLinha(nilo,1));

            if(varEsq < varMinEsq ) varMinEsq = varEsq;
                else if(varEsq > varMaxEsq) varMaxEsq = varEsq;

            if(varDir < varMinDir ) varMinDir = varDir;
                else if(varDir > varMaxDir) varMaxDir = varDir;

        varMediaEsq += varEsq;
        varMediaDir += varDir;
    }
    printf("Margem Esquerda:\n");
    printf("Variacao minima: %d\n",varMinEsq);
    printf("Variacao maxima: %d\n",varMaxEsq);
    printf("Variacao media: %d\n",varMediaEsq/iteracoes);
    printf("\n\n");
    printf("Margem Direita:\n");
    printf("Variacao minima: %d\n",varMinDir);
    printf("Variacao maxima: %d\n",varMaxDir);
    printf("Variacao media: %d\n\n",varMediaDir/iteracoes);

}
