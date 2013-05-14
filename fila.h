#include "terreno.h"

typedef struct fila *Fila;
typedef Terreno* Item;

Fila filaInit();
void insereFila(Fila, Item);
Item removeFila(Fila);
int filaVazia();
void freeFila(Fila);
