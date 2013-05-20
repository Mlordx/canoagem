#include "linhaT.h"


typedef struct lista *List;

typedef linhaT Item;

List listInit();

void mvNext(List list);

void mvPrev(List list);

void mvEOL(List list);

void insertList(List list, Item item);

int removeList(List list);

Item getItem(List list);

int emptyList(List list);

int isEOL(List list);

int nItens(List list);




