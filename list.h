#include "linhaT.h"


typedef struct lista *List;

typedef linhaT Item;

List listInit();

void mvNext(List);

void mvPrev(List);

void mvEOL(List);

void insertList(List, Item);

int removeList(List);

Item getItem(List);

int emptyList(List);

int isEOL(List);

int nItens(List);




