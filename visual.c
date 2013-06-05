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
static void desenhaRioVisual();

/* **************************** */





static int LARGURA_TELA;
static int ALTURA_TELA;
ALLEGRO_DISPLAY *janela = NULL;
Rio rio;
int D = 5;

void visualInit(Rio rioTemp, int dtemp)
{
  D = dtemp;
  rio = rioTemp;
  LARGURA_TELA = D*getLinhaTam(getLinha(rioTemp,1));
  ALTURA_TELA = D*getNLinhas(rioTemp);
  if(!inicializar()) printf("HUE\n");
}
void visualUpdate()
{
  al_clear_to_color(al_map_rgb(255, 255, 255));
  desenhaRioVisual();
  al_flip_display();
}


static void desenhaRioVisual()
{
  linhaT linhaTemp;
  int numLinhas;
  int i,j;

  numLinhas = getNLinhas(rio);

  for(j=1; j<=numLinhas; j++)
  {
    linhaTemp = getLinha(rio,j);
    i = numLinhas + 1 - j;

    /*Margem esquerda*/
    al_draw_filled_rectangle(0,ALTURA_TELA-(i*D), D*getMargEsq(linhaTemp), ALTURA_TELA-((i-1)*D), al_map_rgb(150, 100, 0));


    /* Margem Direita */
    al_draw_filled_rectangle(LARGURA_TELA-(D*(getLinhaTam(linhaTemp)-getMargDir(linhaTemp)) ),ALTURA_TELA-(i*D),LARGURA_TELA , ALTURA_TELA-((i-1)*D), al_map_rgb(150, 100, 0));

  }




}


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
