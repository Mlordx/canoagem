#include "testes.h"
#include <stdlib.h>
#include <stdio.h>

int testaTudo(int iteracoes){
  int i;
  Rio nilo;
  rioInit(nilo);

  printf("Teste de linhas\n");
  printf("Numero de linhas = 10000\n");

  nilo = alocaRio(10000,30,0,0);

    for(i=0;i<iteracoes;i++)
        if(!atualizaRio(nilo)){
            printf("Falha no teste de linhas\n");
            return -1;
        }

  printf("Numero de linhas = 5\n");

  nilo = alocaRio(5,30,0,0);

    for(i=0;i<iteracoes;i++)
        if(!atualizaRio(nilo)){
            printf("Falha no teste de linhas\n");
            return -1;

        }

  printf("Teste de fluxo\n");
  printf("Fluxo = 0.0001\n");
  nilo = alocaRio(100,30,0.0001,0);

    for(i=0;i<iteracoes;i++)
        if(!atualizaRio(nilo)){
            printf("Falha no teste de fluxo\n")
            return -1;
        }
}
