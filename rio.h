#define PROB_OBST 0.3
#define VAR_MARG 1
#define FLUXO_DEFAULT 1
#define TAM_MIN_DEFAULT 5
#define TAM_MIN_BARREIRA 1
#define PORC_MAX_BARREIRA 1

#include "linhaT.h"


typedef struct rio *Rio;

void atualizaRio(Rio);

void rioInit(Rio);

void desenhaRio(Rio);

Rio alocaRio(int lin, int col, float fluxo, int tamMin);

linhaT getLinha(Rio,int);

int getNLinhas(Rio);


