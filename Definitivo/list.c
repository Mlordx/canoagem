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

/*

Essa função retorna uma List vazia, apontando para o EOL.

*/

List listInit()
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



/*

mvNext(List) faz a lista apontar para a próxima célula do
item que a lista aponta atualmente.

*/
void mvNext(List list)
{
  list->celAtual = list->celAtual->prox;
}

/*

mvPrev(List) faz a lista apontar para a célula anterior do
item que a lista aponta atualmente.

*/

void mvPrev(List list)
{
  list->celAtual = list->celAtual->ant;
}

/*
Faz a lista apontar para o EOL da lista
*/

void mvEOL(List list)
{
  list->celAtual = list->cabeca;
}

/*

Insere na lista o item passado como arugmento.
Ele será inserido como uma célula que ficará em sequencia
da célula apontada atualmente pelo pela lista.

*/

void insertList(List list, Item item)
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

/*
Remove da lista a celula que a lista está apontado atualmente.
E a lista passa a apontar para a celula anterior da que foi deletada.

*/

int removeList(List list)
{
  Link celTemp;


  if(isEOL(list)) return -1;

  celTemp = list->celAtual;

  mvPrev(list);

  list->celAtual->prox = celTemp->prox;
  celTemp->prox->ant = celTemp->ant;
  /*itemTemp = celTemp->item;*/
  free(celTemp);
  list->nItens--;
  return 0;

  /*return itemTemp;*/
}

/*
Função que retorna TRUE caso a lista esteja vazia,
e FALSE c.c.

*/
int emptyList(List list)
{
  return (list->cabeca->prox == list->cabeca);
}

/*
Função que retorna TRUE caso a lista esteja apontando para o EOL
e FALSE c.c.
*/
int isEOL(List list)
{
  return (list->celAtual == list->cabeca);
}


/*

Função que retorna o número de itens que a lista possui.

*/
int nItens(List list)
{
  return list->nItens;
}


/*

Função que retorna o item que a lista aponta atualmente.
Caso seja o EOL, retorna NULL.

*/
Item getItem(List list)
{
  if(!isEOL(list)) return list->celAtual->item;
  else return (Item)NULL;
}


