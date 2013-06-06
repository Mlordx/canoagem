#include <stdio.h>
#include <stdlib.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include "allegro5/allegro_acodec.h"

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
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
Rio rio;
int D = 5;

void visualInit(Rio rioTemp, int dtemp)
{
  ALLEGRO_TIMEOUT timeout;
  ALLEGRO_EVENT evento;
  int temEvento;
  int status;



  D = dtemp;
  rio = rioTemp;
  LARGURA_TELA = D*getLinhaTam(getLinha(rioTemp,1));
  ALTURA_TELA = D*(getNLinhas(rioTemp)-1);
  if(!inicializar()) for(;;)printf("HUE");

  while(1)
  {
    al_init_timeout(&timeout, 0.05);

    temEvento = al_wait_for_event_until(fila_eventos, &evento, &timeout);
    if(temEvento && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

   /* desenhaRio(nilo);*/
    visualUpdate();

    status = atualizaRio(rio);
    if(status == FALHA_OBST)
    {
      printf("Falha ao tentar gerar um obstáculo. O programa sera terminado.");
      exit(-1);
    }
    if(status == FALHA_ATUALIZA)
    {
      printf("Falha ao tentar gerar um novo frame. O programa sera terminado.");
      exit(-1);
    }
  }
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
    i = numLinhas - j;

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
        al_draw_filled_rectangle( (inicioObst(linhaTemp)-1)*D ,ALTURA_TELA-(i*D), D*(tamBarreira(linhaTemp)+inicioObst(linhaTemp)-1), ALTURA_TELA-((i-1)*D), al_map_rgb(204, 102, 0));


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

    if (!al_install_audio())
    {
        fprintf(stderr, "Falha ao inicializar o dispositivo de som.\n");
        return 0;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao inicializar os codecs de audio.\n");
        return 0;
    }

    al_reserve_samples(1); /* Gera e reserva 'n' espaço para samples escolhidos pelo usuário. Cada espaço consiste de uma 'voz' dentro  */
                           /* do 'mixer', que será por meio da qual cada sample será reproduzido na saída de som escolhida.             */

    sample = al_load_sample("04. Metal Massacre Attack (Aruê Aruô).wav"); /* Sample é carregado. */

    al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL); /* Faz o sample tocar :D */

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return 0;
    }

    al_set_window_title(janela, "Testando allegro_primitives");

     fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return 0;
    }
     al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return 1;
}
