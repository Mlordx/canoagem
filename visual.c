#include <stdio.h>
#include <stdlib.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "rio.h"
#include "linhaT.h"
#include "terreno.h"
#include "visual.h"


/* *************  Protótipos *************/

static int inicializar();

/* **************************** */





static int LARGURA_TELA;
static int ALTURA_TELA;
ALLEGRO_DISPLAY *janela = NULL;
Rio rio;
int D;

void visualInit(Rio rioTemp, int dtemp)
{
  D = dtemp;
  rio = rioTemp;
  LARGURA_TELA = getLinhaTam(getLinha(rioTemp,1));
  ALTURA_TELA = getNLinhas(rioTemp);
  if(!inicializar()) printf("HUE\n");
}
void visualUpdate();


static int inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a biblioteca Allegro.\n");
        return 0;
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
        return 0;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return 0;
    }

    al_set_window_title(janela, "Testando allegro_primitives");

    return 1;
}
