#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct celula *Celula;

struct celula
{
    Item item;
    Celula prox;
};

struct fila
{
  Celula cabeca;
};


Fila filaInit()
{
  Fila fila = mallocSafe(sizeof *fila);
  fila->cabeca = mallocSafe(sizeof(struct celula));

  fila->cabeca->prox = fila->cabeca;
  return fila;
}

void insereFila(Fila fila, Item novo)
{
    Celula cel = fila->cabeca, novaCabeca;

    novaCabeca = mallocSafe(sizeof(struct celula));
    cel->item = novo;
    novaCabeca->prox = cel->prox;
    cel->prox = novaCabeca;
    fila->cabeca = novaCabeca;
}

Item removeFila(Fila fila)
{
    Celula x, cabeca = fila->cabeca;
    Item item;
    x = cabeca->prox;
    cabeca->prox = x->prox;
    item = x->item;
    free(x);

    return item;
}
void freeFila(Fila fila)
{
    while(!filaVazia(fila))
        removeFila(fila);
    free(fila);
}

int filaVazia(Fila fila)
{
  return (fila->cabeca->prox == fila->cabeca);
}
