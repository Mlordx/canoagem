#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


struct celula
{
    Item item;
    Celula prox;
};


Celula filaInit()
{
  Celula cabeca = mallocSafe(sizeof(struct celula));
  cabeca->prox = cabeca;
  return cabeca;
}

Celula insereFila(Celula cel, Item novo)
{
    Celula novaCabeca;
    novaCabeca = mallocSafe(sizeof(struct celula));
    cel->item = novo;
    novaCabeca->prox = cel->prox;
    cel->prox = novaCabeca;

    return novaCabeca;
}

Item removeFila(Celula cabeca)
{
    Celula x;
    Item item;
    x = cabeca->prox;
    cabeca->prox = x->prox;
    item = x->item;
    free(x);

    return item;
}
void freeFila(Celula cabeca)
{
    while(cabeca->prox!= cabeca)
        removeFila(cabeca);
}
