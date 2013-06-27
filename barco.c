#include <stdio.h>
#include <stdlib.h>
#include "barco.h"
#include "utils.h"




struct barco
{
  Vetor2D pos;
  Vetor2D vel;
  Vetor2D tam;
};

void atualizaBarco(BarcoT barco, int ne, int nd, float ve, float vd)
{
  Vetor2D vel, velAdE, velAdD, velAdT;
  float ang;
  vel = barco->vel;

  setVetorX(vel, getVetorX(vel)*0.8);
  setVetorY(vel, getVetorY(vel)*0.8);

  ang = getAngulo(vel);

  velAdE = novoVetor(ne*0.5+ve, 0);
  rotVetor(velAdE, ang + ne*PI/10);
  velAdD = novoVetor(nd*0.5+vd, 0);
  rotVetor(velAdD, ang - nd*PI/10);

  velAdT = somaVetores(velAdD, velAdE);
  freeVetor(velAdD); freeVetor(velAdE);


  barco->vel = somaVetores(vel, velAdT);
  freeVetor(vel); freeVetor(velAdT);


  setVetorX(barco->pos, getVetorX(barco->pos) + getVetorX(barco->vel));

}


BarcoT novoBarco(Vetor2D pos, Vetor2D vel, Vetor2D tam)
{
    BarcoT barco;
    barco = mallocSafe(sizeof(*barco));

    barco->pos = pos;
    barco->vel = vel;
    barco->tam = tam;

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

