#include <stdio.h>
#include <stdlib.h>
#include "barco.h"
#include "utils.h"





struct barco
{
  Vetor2D pos;
  Vetor2D vel;
  Vetor2D tam;
  int vidas;
};

int setVida(BarcoT barco,int v)
{
 barco->vidas = v;
}
int getVida(BarcoT barco)
{
  return barco->vidas;
}

void atualizaBarco(BarcoT barco, int ne, int nd, float ve, float vd)
{
  Vetor2D vel, velAdE, velAdD, velAdT;
  float ang;
  vel = barco->vel;

  setVetorX(vel, getVetorX(vel)*0.8);
  setVetorY(vel, getVetorY(vel)*0.8);

  ang = getAngulo(vel);

  velAdE = novoVetor(0,ne*0.8+ve);
/*   printf("VelAdE(antes): %f %f %f\n",180*getAngulo(velAdE)/PI, getVetorX(velAdE), getVetorY(velAdD)); */
  rotVetor(velAdE, 2*PI+ ne*PI/4);
  printf("VelAdE: %f %f %f\n",180*getAngulo(velAdE)/PI, getVetorX(velAdE), getVetorY(velAdE));
  velAdD = novoVetor(0,nd*0.8+vd);
  printf("VelAdD(antes): %f %f %f\n",180*getAngulo(velAdD)/PI,getVetorX(velAdD), getVetorY(velAdD));
  rotVetor(velAdD,  -nd*PI/4);
  printf("VelAdD: %f %f %f\n",180*getAngulo(velAdD)/PI,getVetorX(velAdD), getVetorY(velAdD));


 /* ve = ve + ne*0.5;
  vd = vd + nd*0.5;

  ang = atan(1.0/(vd - ve));

  velAdT = novoVetor(0,(ve+vd)/2);

  rotVetor(velAdT, PI/2 - ang);*/








  velAdT = somaVetores(velAdD, velAdE);
 /* printf("VetorAd: %f %f\n",getVetorX(velAdT), getVetorY(velAdT));*/
  freeVetor(velAdD); freeVetor(velAdE);


  barco->vel = somaVetores(vel, velAdT);
  freeVetor(vel); freeVetor(velAdT);


  setVetorX(barco->pos, getVetorX(barco->pos) + getVetorX(barco->vel));

}

int estaBatendo(BarcoT barco, Rio rio)
{
  int i, j, posY, posX, tamY, tamX;
  linhaT linhaTemp;
  Terreno terrTemp;

  posY = getVetorY(barco->pos);
  posX = getVetorX(barco->pos);
  tamY = getVetorY(barco->tam);
  tamX = getVetorX(barco->tam);


  for(i = -tamY; i <= tamY; i++)
  {
    linhaTemp = getLinha(rio,posY + i);
    for(j = -tamX; j <= tamX; j++)
    {
      terrTemp = getTerreno(linhaTemp, posX + j);
      if(getTipo(terrTemp) == TERRA) return 1;
    }
  }

  return 0;
}


BarcoT novoBarco(Vetor2D pos, Vetor2D vel, Vetor2D tam, int vidas)
{
    BarcoT barco;
    barco = mallocSafe(sizeof(*barco));

    barco->pos = pos;
    barco->vel = vel;
    barco->tam = tam;
    barco->vidas = vidas;

    return barco;
}
Vetor2D getVelocidadeBarco(BarcoT barco)
{
    return barco->vel;
}
Vetor2D getPosBarco(BarcoT barco)
{
    return barco->pos;
}
void setVelocidadeBarco(BarcoT barco, Vetor2D vel)
{
    barco->vel = vel;
}
Vetor2D getTamBarco(BarcoT barco)
{
    return barco->tam;
}

