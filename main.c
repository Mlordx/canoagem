#define SEED_DEFAULT 1234567890
#define NUM_LIN_DEFAULT 60
#define NUM_COL_DEFAULT 90
#define FLUXO_DEFAULT 5
#define TAM_MIN_DEFAULT 30
#define ITERACOES_DEFAULT 1000

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "rio.h"
#include "utils.h"
#include "testes.h"
#include "visual.h"
#include <time.h>

/* Variaveis do Bison */


extern int seed, linhas, colunas, it, tamanhoMinimo;
extern float fluxoRio;


/* ------------------------ */


int main(int argc, char* argv[])
{
    Rio nilo;

/* ************************************************/

    int testeLinhas = 0, testeFluxo = 0, testeVariacoes = 0, testeMargem = 0, teste = 0;
    int args;
    yyparse();
    /* Modifica a seed de acordo com o valor passado. */
    srand(seed);
    /* **************************************************************************************************/
    if(argc == 2){
        if(argv[1][0] == '-'){
            switch(argv[1][1]) {
                case 'T':   teste = 1;
                            if(argv[1][2] == '1') testeLinhas = 1;
                            else if(argv[1][2] == '2') testeFluxo = 1;
                            else if(argv[1][2] == '3') testeMargem = 1;
                            else if(argv[1][2] == '4') testeVariacoes = 1;
                            else {
                                printf("Comando inválido.");
                                exit(EXIT_FAILURE);
                            }
                            break;
                default:    printf("Comando inválido.");
                            exit(EXIT_FAILURE);
            }
        }
    }

    /* * Inicializa o rio de acordo com os parâmetros passados pelo usuário. Caso ele não tenha passado, são utilizados valores default. **/

    if(!teste)
    {
          nilo = alocaRio(linhas, colunas, fluxoRio, tamanhoMinimo);
          if(visualInit(nilo,10, 0.01) ==  VISUAL_FAIL) fprintf(stderr,"Erro durante a exibição do rio.\n");
    }
    else
    {
      if(testeVariacoes) testaVariacao(it);

      if(testeFluxo)
      {
        if(testaFluxo(it)) printf("Teste de Fluxo: Sucesso\n");
        else printf("Teste de Fluxo: Fracasso\n");
      }

      if(testeLinhas)
      {
        if(testaLinhas(it)) printf("Teste de Linhas: Sucesso\n");
        else printf("Teste de Linhas: Fracasso\n");
      }

      if(testeMargem)
      {
        if(testaMargem(it)) printf("Teste de Margem: Sucesso\n");
        else printf("Teste de Margem: Fracasso\n");
      }


    }
    return 0;
}
