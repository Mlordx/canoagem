#include "linhaT.h"


typedef struct lista *List;

typedef linhaT Item;

List listaInit();

void mvNext(List);

void mvPrev(List);

void mvEOL(List);

void insertItem(List, Item);

Item removeItem(List);

int emptyList(List);

int isEOL(List);




