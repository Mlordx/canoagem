#define SEED_DEFAULT 1234567890
#define NUM_LIN_DEFAULT 30
#define NUM_COL_DEFAULT 100
#define FLUXO_DEFAULT 1
#define TAM_MIN_DEFAULT 5
#define ITERACOES_DEFAULT 1000

#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "utils.h"
#include "testes.h"
#include <time.h>

int main(int argc, char* argv[])
{
    Rio nilo;

/* ************************************************/
    int seed = SEED_DEFAULT, args;
    int linhas = NUM_LIN_DEFAULT, status;
    int colunas = NUM_COL_DEFAULT, it = ITERACOES_DEFAULT;
    int testeLinhas = 0, testeFluxo = 0, testeVariacoes = 0, testeMargem = 0, teste = 0;

    int tamanhoMinimo = TAM_MIN_DEFAULT;
    float fluxoRio = FLUXO_DEFAULT;

    if(argc >= 2){
        for(args = 1; args < argc; args++){
            if(argv[args][0] == '-'){
                switch(argv[args][1]) {
                    /* Tudo que precisa é adcionar novos casos necessários aqui e as variáveis correspondentes à cada scanf :D .*/
                    case 'L':   sscanf(argv[args], "-L%d", &linhas);
                                break;
                    case 'C':   sscanf(argv[args], "-C%d", &colunas);
                                break;
                    case 's':   sscanf(argv[args], "-s%d", &seed);
                                break;
                    case 't':   sscanf(argv[args], "-t%d", &tamanhoMinimo);
                                break;
                    case 'F':   sscanf(argv[args], "-F%f", &fluxoRio);
                                break;

                    case 'I':   sscanf(argv[args], "-I%d", &it);
                                break;
                    /* ***************************************/
                    case 'T':   teste = 1;
                                if(argv[args][2] == '1') testeLinhas = 1;
                                if(argv[args][2] == '2') testeFluxo = 1;
                                if(argv[args][2] == '3') testeMargem = 1;
                                if(argv[args][2] == '4') testeVariacoes = 1;
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
        /* Modifica a seed de acordo com o valor passado. */
        srand(seed);
        /* **************************************************************************************************/

    }
    /* * Inicializa o rio de acordo com os parâmetros passados pelo usuário. Caso ele não tenha passado, são utilizados valores default. **/

    if(!teste)
    {
          nilo = alocaRio(linhas, colunas, fluxoRio, tamanhoMinimo);
          while(1)
          {
              desenhaRio(nilo);

              meuSleep(100);

              system("clear");
              status = atualizaRio(nilo);
              if(status == FALHA_OBST)
              {
                printf("Falaha ao tentar gerar um obstáculo. O programa sera terminado.");
                exit(-1);
              }
              if(status == FALHA_ATUALIZA)
              {
                printf("Falaha ao tentar gerar um novo frame. O programa sera terminado.");
                exit(-1);
              }
          }
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
