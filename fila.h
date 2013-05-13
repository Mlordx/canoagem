#include "terreno.h"

typedef struct celula *Celula;
typedef Terreno* Item;

Celula filaInit();
Celula insereFila(Celula, Item);
Item removeFila(Celula);
void freeFila(Celula);
