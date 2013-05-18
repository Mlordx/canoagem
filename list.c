#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

struct celula
{
  Item item;
  struct celula* prox;
  struct celula* ant;
};
typedef struct celula *Link;

struct lista
{
  Link cabeca;
  Link celAtual;
  int nItens;

};

List listaInit()
{
  List list;
  list = mallocSafe(sizeof *list);
  list->cabeca = mallocSafe(sizeof (struct celula));
  list->cabeca->prox = list->cabeca;
  list->cabeca->ant = list->cabeca;
  list->celAtual = list->cabeca;
  list->nItens = 0;

  return list;
}

void mvNext(List list)
{
  list->celAtual = list->celAtual->prox;
}

void mvPrev(List list)
{
  list->celAtual = list->celAtual->ant;
}

void mvEOL(List list)
{
  list->celAtual = list->cabeca;
}

void insertItem(List list, Item item)
{
  Link newCel;
  newCel = mallocSafe(sizeof(struct celula));
  newCel->item = item;
  newCel->ant = list->celAtual;
  newCel->prox = list->celAtual->prox;
  list->celAtual->prox->ant = newCel;
  list->celAtual->prox = newCel;
  list->nItens++;
}

Item removeItem(List list)
{
  Link celTemp;
  Item itemTemp;

  if(isEOL(list)) return NULL;

  celTemp = list->celAtual;
  mvPrev(list);
  list->celAtual->prox = celTemp->prox;
  celTemp->prox->ant = celTemp->ant;
  itemTemp = celTemp->item;
  free(celTemp);
  list->nItens--;

  return itemTemp;
}

int emptyList(List list)
{
  return (list->cabeca->prox == list->cabeca);
}

int isEOL(List list)
{
  return (list->celAtual == list->cabeca);
}

