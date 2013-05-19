#define SEED_DEFAULT 1234567890
#define NUM_LIN_DEFAULT 30
#define NUM_COL_DEFAULT 100
#define FLUXO_DEFAULT 1
#define TAM_MIN_DEFAULT 5

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
    int linhas = NUM_LIN_DEFAULT;
    int colunas = NUM_COL_DEFAULT;
    int testeLinhas = 0, testeFluxo = 0, testeVariacoes = 0, testeMargem = 0;

    int tamanhoMinimo = TAM_MIN_DEFAULT;
    int fluxoRio = FLUXO_DEFAULT;

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
                    case 'F':   sscanf(argv[args], "-F%d", &fluxoRio);
                                break;
                    /* ***************************************/
                    case 'T':   if(argv[args][2] == '1') testeLinhas = 1;
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
    nilo = alocaRio(linhas, colunas, fluxoRio, tamanhoMinimo);
    rioInit(nilo);


/* ************************************************/
    while(1)
    {
        desenhaRio(nilo);

        meuSleep(100);

        system("clear");
        atualizaRio(nilo);
    }
    return 0;
}
