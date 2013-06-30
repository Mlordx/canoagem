#include <stdio.h>
#include <stdlib.h>

#define TEMPO_INV 1
#define MS_INV 0.02

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



#include "rio.h"
#include "linhaT.h"
#include "utils.h"
#include "terreno.h"
#include "visual.h"
#include "vetor2D.h"
#include "barco.h"



/* *************  Protótipos *************/
static void visualUpdate(Rio rio);
static int inicializar();
static void desenhaRioVisual(Rio rio);
static void  desenhaBarco(BarcoT, int, int, Rio);

/* **************************** */





static int LARGURA_TELA;
static int ALTURA_TELA;
static ALLEGRO_DISPLAY *janela = NULL;
static ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
static ALLEGRO_BITMAP  *image   = NULL;
static ALLEGRO_BITMAP  *imagemVida   = NULL;
static ALLEGRO_FONT *font = NULL;
static int D = 5;
static BarcoT barco;
static int inv = 0;
static int score = 0;
static int GAME_OVER = 0;

int visualInit(Rio rioTemp, int dtemp, float ms)
{
  ALLEGRO_TIMEOUT timeout;
  ALLEGRO_EVENT evento;
  int temEvento;
  int status = VISUAL_SUCCESS;
  int ne,nd;
  float tempoInicial;
  int sair = 0;
  float vy;
  Rio rio;

  D = dtemp;
  rio = rioTemp;
  LARGURA_TELA = D*getLinhaTam(getLinha(rioTemp,1));
  ALTURA_TELA = D*(getNLinhas(rioTemp)-1);

   barco = novoBarco(novoVetor(LARGURA_TELA/(2*D), (ALTURA_TELA/D) - 20) , novoVetor(0,1.5), novoVetor(45.0/(2*D), 60.0/(2*D)),3);

  if(!inicializar()) return VISUAL_FAIL;

  while(!GAME_OVER)
  {
    if(inv) ms = MS_INV;
    al_rest(ms);
    if((vy = getVetorY(getVelocidadeBarco(barco)) ) < 3 && vy > 0) ms = 0.03 - (getVetorY(getVelocidadeBarco(barco)))/100;
   /* printf("TEMPO: %f ms\n", ms);*/

    ne = nd = 0;
   /* temEvento = al_wait_for_event_until(fila_eventos, &evento, &timeout);*/
   tempoInicial = al_get_time();
    while (!al_is_event_queue_empty(fila_eventos) && al_get_time() - tempoInicial < ms)
    {
        al_wait_for_event(fila_eventos, &evento);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {GAME_OVER = 1; break;}
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(evento.keyboard.keycode)
            {

              case ALLEGRO_KEY_LEFT:
                ne++;
                break;
              case ALLEGRO_KEY_RIGHT:
                nd++;
                break;
             }

        }

    }

    score += 1;

    visualUpdate(rio);
    al_draw_textf(font, al_map_rgb(0,0,0), LARGURA_TELA-100, 0, ALLEGRO_ALIGN_RIGHT ,"Score: %d", score);
    desenhaBarco(barco, ne, nd, rioTemp);
    al_flip_display();

    status = atualizaRio(rio);
    if(status == FALHA_OBST)
      fprintf(stderr,"Falha ao tentar gerar um obstáculo.\n");
    if(status == FALHA_ATUALIZA)
    {
      fprintf(stderr,"Falha ao tentar gerar um novo frame. O programa sera terminado.\n");
      status = VISUAL_FAIL;
      break;
    }
  }

  al_destroy_display(janela);
  al_destroy_bitmap(image);
  return status;

}


void visualUpdate(Rio rio)
{
  al_clear_to_color(al_map_rgb(153, 204, 255));
  desenhaRioVisual(rio);

}



static void desenhaBarco(BarcoT barco, int ne, int nd, Rio rio)
{
    Vetor2D pos, tam, vel;
    float ve, vd, posX, posY, tamX;
    int nLinhas;
    int i;
    Terreno terrTemp;
    linhaT linhaTemp;
    pos = getPosBarco(barco);
    tam = getTamBarco(barco);
    vel = getVelocidadeBarco(barco);

     posX = getVetorX(pos);
     posY = getVetorY(pos);
     tamX = getVetorX(tam);

    i = 0;


    nLinhas = getNLinhas(rio);
    linhaTemp = getLinha(rio,getVetorY(pos));
    /*terrTemp = getTerreno(linhaTemp, posX-1);
    setTipo(terrTemp, TERRA);
    desenhaRio(rio);
    printf("\033[2J\033[1;1H");*/
    ve = getVelocidade( getTerreno(linhaTemp, posX-tamX/2) );
    vd = getVelocidade( getTerreno(linhaTemp, posX+tamX/2) );

     /*printf("HUE: %f  %f   %f\n\n", getVetorX(vel), getVetorY(vel), getAngulo(vel));*/
    atualizaBarco(barco, ne, nd, ve, vd);
    if(estaBatendo(barco, rio) && !inv){
       setVida(barco, getVida(barco)-1);
       setVetorX(pos, LARGURA_TELA/(2*D));
       if(getVida(barco) <= 0){
           i = al_show_native_message_box(NULL, "Canoagem","Você Perdeu!", "Deseja recomeçar?",NULL, ALLEGRO_MESSAGEBOX_YES_NO);
           if(i == 1){
               setVida(barco, 3);
               setVetorX(pos, LARGURA_TELA/(2*D));
               score = 0;
           }
            else if(!i || i == 2){
                GAME_OVER = 1;
            }
       }
       inv = TEMPO_INV/MS_INV;
    }

    if(inv) inv--;

    for(i = 0; i < getVida(barco); i++){
      al_draw_scaled_bitmap(imagemVida, D, D , 164, 120,D+ i*41, D , 41, 30, NULL);
    }

    posX = getVetorX(pos);
    posY = getVetorY(pos);

    pos = getPosBarco(barco);
    tam = getTamBarco(barco);
    vel = getVelocidadeBarco(barco);



  /* Elipse preenchido: x1, y1, raio x, raio y, cor*/
  /*al_draw_filled_ellipse(getVetorX(pos)*D,getVetorY(pos)*D , getVetorX(tam)*D, getVetorY(tam)*D, al_map_rgb(166,42,42));*/

  if(inv%2 == 0) al_draw_rotated_bitmap(image,22,30, posX*D,posY*D,-(getAngulo(vel)+PI/2),ALLEGRO_FLIP_VERTICAL);
 /* printf("HUE: %f\n",180*getAngulo(vel)/PI);
  printf("Velocidade: %f %f\n", getVetorX(vel), getVetorY(vel));*/
}



static void desenhaRioVisual(Rio rio)
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

   if(!al_init_image_addon()){
        fprintf(stderr, "Falha ao inicializar o add-on de imagens.\n");
        return 0;
   }

  image = al_load_bitmap("BarcoBoladoV2.png");

  if(!image) {
      fprintf(stderr,"Falha ao carregar Imagem!\n");
      return 0;
   }

   imagemVida = al_load_bitmap("coracao.png");

  if(!imagemVida) {
      fprintf(stderr,"Falha ao carregar Imagem!\n");
      return 0;
   }

   al_init_font_addon();


   al_init_ttf_addon();

   font = al_load_ttf_font("interstate-black.ttf",38,0 );



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

    al_set_window_title(janela, "EP3 - LAB PROG I");



     fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return 0;
    }
     al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return 1;
}
