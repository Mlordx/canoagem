#include "linhaT.h"

typedef struct fila *Fila;
typedef linhaT Item;

Fila filaInit();
void insereFila(Fila, Item);
Item removeFila(Fila);
int filaVazia();
void freeFila(Fila);
