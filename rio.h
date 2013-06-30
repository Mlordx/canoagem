#ifndef RIO_H
#define RIO_H


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

#endif


