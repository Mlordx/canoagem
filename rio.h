#define PROB_OBST 0.3
#define VAR_MARG 1
#define TAM_MIN_BARREIRA 1
#define PORC_MAX_BARREIRA 1

#define FALHA_OBST -1
#define FALHA_ATUALIZA 0
#define SUCESSO_ATUALIZA 1

#include "linhaT.h"


typedef struct rio *Rio;

int atualizaRio(Rio);

void desenhaRio(Rio);

Rio alocaRio(int lin, int col, float fluxo, int tamMin);

linhaT getLinha(Rio,int);

int getNLinhas(Rio);


