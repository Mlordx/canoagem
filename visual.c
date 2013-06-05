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
  if(!inicializar()) for(;;)printf("HUE");
}


void visualUpdate()
{
  al_clear_to_color(al_map_rgb(153, 204, 255));
  desenhaRioVisual();
  al_flip_display();
}


static void desenhaRioVisual()
{
  linhaT linhaTemp, linhaTempProx;
  int numLinhas;
  int i,j;
  int posDir, posDirProx;
  int posEsq, posEsqProx;

  numLinhas = getNLinhas(rio);

  for(j=1; j<numLinhas; j++)
  {
    linhaTemp = getLinha(rio,j);
    linhaTempProx = getLinha(rio,j+1);
    i = numLinhas + 1 - j;

    posEsq = getMargEsq(linhaTemp);
    posEsqProx = getMargEsq(linhaTempProx);

    /*Margem esquerda*/
    al_draw_filled_rectangle(0,ALTURA_TELA-((i-1)*D), D*(posEsq-1), ALTURA_TELA-(i*D), al_map_rgb(204, 102, 0));
    if(posEsq>posEsqProx)
        al_draw_filled_triangle(D*(posEsq), ALTURA_TELA-(i*D), D*(posEsqProx), ALTURA_TELA-((i-1)*D),  D*(posEsqProx), ALTURA_TELA-(i*D), al_map_rgb(204, 102, 0));
    else
    {
        al_draw_filled_rectangle( D*(posEsq-1) ,ALTURA_TELA-((i-1)*D), D*(posEsq), ALTURA_TELA-(i*D), al_map_rgb(204, 102, 0));
        if(posEsq<posEsqProx)
        al_draw_filled_triangle(D*(posEsq), ALTURA_TELA-(i*D), D*(posEsq), ALTURA_TELA-((i-1)*D),  D*(posEsqProx), ALTURA_TELA-((i-1)*D), al_map_rgb(204, 102, 0));
    }


    if(tamBarreira(linhaTemp))
        /* Desenha Barreira */
        al_draw_filled_rectangle(inicioObst(linhaTemp)*D,ALTURA_TELA-(i*D), D*(tamBarreira(linhaTemp)+inicioObst(linhaTemp)), ALTURA_TELA-((i-1)*D), al_map_rgb(204, 102, 0));


    posDir = getMargDir(linhaTemp);
    posDirProx = getMargDir(linhaTempProx);

    /* Margem Direita */
    al_draw_filled_rectangle( (D*(posDir+1) ),ALTURA_TELA-(i*D),LARGURA_TELA , ALTURA_TELA-((i-1)*D), al_map_rgb(204, 102, 0));
    if(posDir<posDirProx)
        al_draw_filled_triangle( D*posDir, ALTURA_TELA-(i*D), D*posDirProx, ALTURA_TELA-((i-1)*D),  D*posDirProx, ALTURA_TELA-(i*D), al_map_rgb(204, 102, 0));
    else
    {
        al_draw_filled_rectangle( D*(posDir+1) ,ALTURA_TELA-((i-1)*D), D*posDir, ALTURA_TELA-(i*D), al_map_rgb(204, 102, 0));
        if(posDir>posDirProx)
        al_draw_filled_triangle(D*(posDir), ALTURA_TELA-(i*D), D*(posDir), ALTURA_TELA-((i-1)*D),  D*(posDirProx), ALTURA_TELA-((i-1)*D), al_map_rgb(204, 102, 0));
    }

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
